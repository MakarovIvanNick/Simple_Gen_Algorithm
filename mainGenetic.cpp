//VAR - 3(A)
#include <iostream>
#include <ctime>
#include <vector>
#include <math.h>
using namespace std;
//�����
class individual
{
public:
	individual();
	void show_gene();
	vector<int> gene;
};
//���������
class population
{
public:
	double fit(int x, int y);
	void show_pop();
	void create_population(individual i1);
	double sum_fit();
	void prob_pop();
	void fitness_pop();
	void roulette(int num);
	void mutation();
	void pop_cross();
	bool condition();
	void get_uniq_individ();
private:
	vector<individual>init_pop;
	vector<double>fit_pop;
	vector<double>fit_prob;
	vector<individual>selection_pop;
};

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "ru");
	//�������� ��������� ���������
	population first;
	for (int i = 0; i < 10; i++)
	{
		individual i1;
		first.create_population(i1);
	}
	first.show_pop();
	while (true)
	{
		first.fitness_pop();
		first.prob_pop();
		first.roulette(5);
		first.mutation();
		first.pop_cross();
		if (first.condition() == true)
		{
			cout << " The latest generation " << endl;
			first.show_pop();
			break;
		}
		first.get_uniq_individ();
		first.show_pop();
	}
	return 0;
}

individual::individual()
{
	for (int i = 0; i < 2; i++)	gene.push_back(rand() % 10);
}

void individual::show_gene()
{
	cout << "[ ";
	for (int i = 0; i < gene.size(); i++)
		cout << gene[i] << " ";
	cout << "]";
}

void population::create_population(individual i1)
{
	init_pop.push_back(i1);
}

void population::show_pop()
{
	for (int i = 0; i < init_pop.size(); i++)
	{
		init_pop[i].show_gene();
		cout << " ";
	}
	cout << endl;
}

double population::fit(int x,int y)
{
	return 1 / (pow(x, 2) - y + 4);
}

double population::sum_fit()
{
	double sum = 0;
	for (int i = 0; i < fit_pop.size(); i++)
	{
		sum += fit_pop[i];
	}
	return sum;
}

void population::prob_pop()
{
	for (int i = 0; i < init_pop.size(); i++)
	{
		cout << "The probability of crossing an individual " << i << " equal to: " << fit_pop[i] / sum_fit() << endl;
		fit_prob.push_back(fit_pop[i] / sum_fit());
	}
	//cout << endl << fit_pop.size() << endl;
}

void population::fitness_pop()
{
	for (int i = 0; i < init_pop.size(); i++)
	{
		cout << "Fitness of the individual " << i << " equal to: " << fit(init_pop[i].gene[0], init_pop[i].gene[1]) << endl;
		fit_pop.push_back(fit(init_pop[i].gene[0], init_pop[i].gene[1]));
	}
}

void population::roulette(int num)
{
	vector<individual> chosen;
	while (chosen.size() == 0)
	{
		for (int i = 0; i < num; i++)
		{
			double r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);//0 - 1 rand
			//cout << r << " r - roulette " << endl;
			double prob_circle = 0;
			for (int i = 0; i < fit_prob.size(); i++)
			{
				prob_circle += fit_prob[i];
				if (r <= prob_circle)
				{
					chosen.push_back(init_pop[i]);
					break;
				}
			}
		}
	}
	/*if (chosen.size() == 0)
		selection_pop = init_pop;
	else*/
	selection_pop = chosen;
}

void population::mutation()
{
	double Pm = 1 / 2;
	for (int i = 0; i < selection_pop.size(); i++)
	{
		double r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		//cout << r << " r - mytation " << endl;
		for (int j = 0; j < selection_pop[i].gene.size(); j++)
		{
			if (Pm > r)
			{
				selection_pop[i].gene[0] += 1;
			}
		}
	}
}

void population::pop_cross()
{
	vector<individual>new_pop;
	new_pop.resize(init_pop.size());
	double Pc = 0.6;
	int k = 0;
	while (k < init_pop.size())
	{
		double r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		int size_pop = selection_pop.size();
		//cout << "Size_pop: " << size_pop << endl;
		//cout << r << " r - pop_cross " << endl;
		if (Pc > r)
		{
			int rand_individ_x = rand() % selection_pop.size(), rand_individ_y = rand() % selection_pop.size();
			new_pop[k].gene[0] = selection_pop[rand_individ_x].gene[0];
			new_pop[k].gene[1] = selection_pop[rand_individ_y].gene[1];
			//new_pop[k].push_b(selection_pop[rand_individ_x].gene[0], selection_pop[rand_individ_y].gene[1]);
		}
		else
		{
			int rand_individ = rand() % selection_pop.size();
			//new_pop[k].push_b(selection_pop[k].gene[0], selection_pop[k].gene[1]);
			new_pop[k].gene[0] = selection_pop[rand_individ].gene[0];
			new_pop[k].gene[1] = selection_pop[rand_individ].gene[1];
		}
		k++;
	}
	init_pop = new_pop;
}

bool population::condition()
{
	for (int i = 0; i < init_pop.size(); i++)
		for (int j = 0; j < init_pop[i].gene.size(); j++)
			if (init_pop[i].gene[0] == 0 && init_pop[i].gene[1] == 4)
				return true;
	return false;
}

void population::get_uniq_individ()
{
	vector<individual> new_pop = init_pop;
	for (int i = 0; i < init_pop.size(); i++)
		for(int j = 0; j<new_pop.size();j++)
			if (init_pop[i].gene[0] == new_pop[j].gene[0] && init_pop[i].gene[1] == new_pop[j].gene[1])
			{
				new_pop[j].gene[0] = i;
				new_pop[j].gene[1] = j;
			}
	init_pop = new_pop;
}