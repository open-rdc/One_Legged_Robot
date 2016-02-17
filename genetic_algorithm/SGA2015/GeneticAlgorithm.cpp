#include "GeneticAlgorithm.h"

template <typename T> std::string tostr(const T& t)
{
    std::ostringstream os; os<<t; return os.str();
}

#ifndef CHECK_ALGORITHM
GA::GA(): utility(), serial(), fm(), fmg(), ofs()
{
	serial.Init();
#else
GA::GA(): utility(), fm(), fmg(), ofs()
{
#endif
}

GA::~GA()
{
#ifndef CHECK_ALGORITHM
	serial.close();
#endif
}


/*
 * @brief 初期値の読み出し
 * 個体の初期値の読み出し
 */
bool GA::LoadInitFile()
{
	FileManager *fm = new FileManager();
	if(!fm->OpenInputFile("RandomParameter.csv"))		// どちらが使用されている？
	{
		fm = new FileManager();
		if(!fm->OpenInputFile("Parameter.csv"))
		{
			return false;
		}
	}

	for(int i=0; i<RANDOM_MAX; i++)
	{
		for(int j=0; j<PARAMETER_NUM; j++)
		{
			angle[i][j] = fm->GetData();
			ofs << angle[i][j] << "\t";
		}
	}

	fm->CloseInputFile();
	return true;
}

/*!
 * @brief 初期化
 */
void GA::Initialize()
{
	if(!LoadInitFile())
	{
		std::cout << "----- Initialize -----" << std::endl;
		ofs.open((utility.GetTimeISOString() + ".csv").c_str());
		ofs << "Initialize" << std::endl;

		utility.Random(0, 450, 0);
		utility.Random(0, 450, 1);

		for(int i=0; i<RANDOM_MAX; i++)
		{
			for(int j=0; j<PARAMETER_NUM; j++)
			{
				angle[i][j] = utility.GetRandom(i, j);
				ofs << angle[i][j] << "\t";
			}
		}
	}

	SaveRandomParameter();
	fmg.OpenOutputFile("GenerationParameter.csv");
	fm.OpenOutputFile("EvaluateValue.csv");
	fm.PutData("ParameterNo:");
	for(int i=0;i<RANDOM_MAX;i++)
	{
		fm.PutData(i+1);
	}
	fm.PutEndline();
	ofs << std::endl;
}

/*!
 * @brief 角度を文字に変換
 */
void GA::MakeSring()
{
	ResetStr();

	for(int i=0; i<RANDOM_MAX; i++)
	{
		for(int j=0; j<PARAMETER_NUM; j++)
		{
			if(j != 2)
			{
				str[i] += tostr(angle[i][j] - ZERO_POINT);
			}
			else
			{
				str[i] += tostr(angle[i][j]);
			}
			str[i] += ",";
			
			if(j == PARAMETER_NUM-1)
			{
				str[i] += "\n";
			}
		}
	}
}

/*!
 * @brief １世代分ロボットにパラメータを送り，結果をmove_resultに入れる．
 */
void GA::RobotMove()
{
	int enc;
	ofs << "move_result" << std::endl;
	fm.PutData("Loop Count:");
	fm.PutData(loopNo+1);
	fm.PutEndline();
	fm.PutData(" ");
	for(int i=0; i<RANDOM_MAX; i++)
	{
#ifndef CHECK_ALGORITHM
		serial.BoostWrite("s");
		for(int j=0; j<5; j++)
		{
			serial.BoostWrite(str[i]);
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		std::cout << "str[" << i << "]: " << str[i];
		boost::this_thread::sleep(boost::posix_time::seconds(SLEEP_TIME));
		for(int k=0; k<100; k++)
		{
			serial.BoostRead();
			boost::this_thread::sleep(boost::posix_time::milliseconds(50));
		}
		enc = serial.GetSerialBuf();
#else
		int ang1, ang2;
		{
			sscanf(str[i].c_str(), "%d,%d", &ang1, &ang2);
			enc = abs(ang1 + ang2 - 50) - 225;				// 実験条件１
//			enc = (ang1 + ang2 - 50) - 225;					// 実験条件２
		}
#endif
		std::cout << "ReadEnc: " << enc << std::endl << std::endl;
		move_result[i] = enc;
		fm.PutData(enc);
		ofs << move_result[i] << "\t";
	}
	fm.PutEndline();
	ofs << std::endl;
}

/*!
 * @brief 選択
 */
void GA::Selection()
{
	int temp, angle_temp;
	int target[RANDOM_MAX][2];
	int parent_cpy = 0;

	std::cout << "----- Selection -----" << std::endl;
	ofs << "Selection" << std::endl;

	for(int i=0; i<RANDOM_MAX; i++)
	{
		target[i][0] = move_result[i];
		target[i][1] = i;
	}

	// ソート
	for(int j=0; j<RANDOM_MAX-1; j++)
	{
		for(int k=j+1; k<RANDOM_MAX; k++)
		{
			if(target[j][0] < target[k][0])
			{
				temp = target[j][0];
				angle_temp = target[j][1];
				target[j][0] = target[k][0];
				target[j][1] = target[k][1];
				target[k][0] = temp;
				target[k][1] = angle_temp;
			}
		}
	}

	// 選択
	for(int l=0; l<INDIVIDUALS_NUMBER; l++)
	{
		for(int m=0; m<2; m++)
		{
			result[l][m] = target[l][m];
		}
	}

	// 選択した個体を繰り返しバイナリにして全体の個体にセット
	for(int n=0; n<PARAMETER_NUM; n++)
	{
		for(int o=0; o<RANDOM_MAX; o++)
		{
			if(parent_cpy == INDIVIDUALS_NUMBER)
			{
				parent_cpy = 0;
			}
			parent[o][n] = utility.BinaryToDecimal(angle[result[parent_cpy][1]][n]);
			ofs << angle[result[parent_cpy][1]][n] << "\t";
			parent_cpy += 1;
		}
	}
	ofs << std::endl;
}

/*
 * @brief 交叉
 * 2015 隣の個体と交叉，エリート保存戦略なし
 * 林原　エリート保存戦略，ランダムに交叉
 */

void GA::Crossover()
{
	std::bitset<32> mask = utility.GetMask();
	int counter = 0, val;
	std::cout << "----- Crossover -----" << std::endl;
	ofs << "Crossover" << std::endl;

	for(int i = 0; i < INDIVIDUALS_NUMBER; i++)
	{
		for(int k = 0; k < PARAMETER_NUM; k++)
		{
			child[i][k] = parent[i][k];
		}
	}
	for(int i = INDIVIDUALS_NUMBER; i < RANDOM_MAX; i++)
	{
		mask = utility.GetMaskRandom();
		int selected_no = utility.Random(0, INDIVIDUALS_NUMBER - 1);
		for(int k = 0; k < PARAMETER_NUM; k++)
		{
			for(size_t j = 0; j < parent[i][k].size(); j++)
			{
				if(mask.test(j) == 0)
				{
					child[i][k].set(j, parent[i          ][k].test(j));
				}
				else
				{
					child[i][k].set(j, parent[selected_no][k].test(j));
				}
			}
			val = child[i          ][k].to_ulong();
			if (val > 450) child[i          ][k] = utility.BinaryToDecimal(450);

			ofs << utility.DecimalToBinary(child[i          ][k]) << "\t";
		}
	}
	ofs << std::endl;
}

void GA::Mutation()
{
	double random;
	int mutation_pos;
	std::cout << "----- Mutation -----" << std::endl;
	ofs << "Mutation" << std::endl;

	for(int j=INDIVIDUALS_NUMBER; j<PARAMETER_NUM; j++)
	{
		for(int i=0; i<RANDOM_MAX; i++)
		{
			random = utility.Random(0, 100) * 0.01;

			if(random <= MUTATION_RATE)
			{
				mutation_pos = utility.Random(0, MUTATION_POS);
				child[i][j].flip(mutation_pos);
				int val = child[i][j].to_ulong();
				if ((val > 450)||(val < 0)) child[i][j] = utility.BinaryToDecimal(450);
			}
		}
	}

	for(int k=0; k<PARAMETER_NUM; k++)
	{
		for(int l=0; l<RANDOM_MAX; l++)
		{
			angle[l][k] = utility.DecimalToBinary(child[l][k]);
			ofs << angle[l][k] << "\t";
		}
	}
	ofs << std::endl;
}

void GA::ResetStr()
{
	for(int i=0; i<RANDOM_MAX; i++)
	{
		str[i] = "";
	}
}

/*
 * @brief 初期化ファイルの保存
 */
void GA::SaveParameter()
{
	FileManager fm;
	fm.OpenOutputFile("Parameter.csv");
	for(int i=0;i<RANDOM_MAX;i++)
	{
		for(int j=0;j<PARAMETER_NUM;j++)
		{
			fm.PutData(angle[i][j]);
		}
		fm.PutEndline();
	}
	fm.CloseOutputFile();
}

/*
 * @brief 初期化ファイルの保存
 */
void GA::SaveRandomParameter()
{
	FileManager fm;
	fm.OpenOutputFile("RandomParameter.csv");
	for(int i=0;i<RANDOM_MAX;i++)
	{
		for(int j=0;j<PARAMETER_NUM;j++)
		{
			fm.PutData(angle[i][j]);
		}
		fm.PutEndline();
	}
	fm.CloseOutputFile();
}

void GA::SaveGenerationParameter(){
	fmg.PutData("LoopCount:");
	fmg.PutData(loopNo+1);
	fmg.PutEndline();
	for(int i=0;i<RANDOM_MAX;i++){
		for(int j=0;j<PARAMETER_NUM;j++){
			fmg.PutData(angle[i][j]);
		}
		fmg.PutEndline();
	}
	fmg.PutEndline();
}

int main()
{
	GA ga;
	ga.Initialize();

	for(ga.loopNo=0; ga.loopNo<LOOP_COUNT; ga.loopNo++)
	{
		std::cout << "LOOP_COUNT: " << ga.loopNo+1 << std::endl;

		ga.SaveGenerationParameter();

		ga.MakeSring();
		ga.RobotMove();
		
		ga.Selection();
		ga.Crossover();
		ga.Mutation();
	}
	ga.SaveParameter();

	return 0;
}