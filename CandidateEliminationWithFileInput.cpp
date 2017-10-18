#include <bits/stdc++.h>

using namespace std;


// Notations used in commenting:

// h -> current hypothesis being considered
// d -> current training example
// G -> Current set of Generic hypothesis
// S -> Current set of Specific hypothesis


// Function to check if hypothesis temp1 is more general than hypothesis temp2
int more_general_than(vector<string> &temp1, vector<string> &temp2)
{
	int i;
	for(i = 0; i < 16; i++)
	{
		if(temp1[i] == "?" || temp2[i] == "-1" || temp1[i] == temp2[i]) continue;
		else return 0;
	}
	return 1;
}


// If positive example is encountered
void positive(string animal, vector<string> &input, vector< vector<string> > &generic, vector< vector<string> >&specific)
{
	int i, j, flag;

	// Remove from G any hypothesis inconsistent with d
	for(i = 0; i < generic.size(); i++)
	{
		for(j = 0; j < 16; j++)
		{
			if(generic[i][j] == "?" || generic[i][j] == input[j]) continue;
			else
			{
				generic.erase(generic.begin() + i);
				i--;
				break;
			}
		}
	}


	for(i = 0; i < specific.size(); i++)
	{
		flag = 0;
		for(j = 0; j < 16; j++)
		{
			if(specific[i][j] == "?" || specific[i][j] == input[j]) continue;
			else
			{
				flag = 1;
				break;
			}
		}
		// For hypothesis in S which is inconsistent with d, flag = 1
		if(flag == 1)
		{
			for(j = 0; j < 16; j++)
			{
				if(specific[i][j] == "-1")
					specific[i][j] = input[j];
				else if(specific[i][j] != "?" && specific[i][j] != input[j])
					specific[i][j] = "?";
			}

			// specific.erase(specific.begin() + i);
			// i--;
			flag = 0;

			// Checking if some member of G is more general than h
			for(j = 0; j < generic.size(); j++)
			{
				if(more_general_than(generic[j], specific[i]))
				{
					flag = 1;
					break;
				}
			}

			// If there is no hypothesis in G which is more general than h, concept cannot be learned
			if(flag == 0)
			{
				cout << "Concept cannot be learned for animal class " + animal << endl;
			}
			flag = 0;
			// Remove from S any hypothesis that is more general than another hypothesis in S
		}
	}
}

// If a negative example is encountered
void negative(string animal, vector<string> &input, vector< vector<string> > &generic, vector< vector<string> >&specific)
{
	int i, j, k, flag, flager, flager1, flager2, flager3, flager4, flager5, leave_loop, leave_loop1, leave_loop2, leave_loop3, leave_loop4, leave_loop5;

	// Remove from S any hypothesis inconsistent with d
	for(i = 0; i < specific.size(); i++)
	{
		flag = 0;
		for(j = 0; j < 16; j++)
		{
			if(specific[i][j] == "?" || specific[i][j] == input[j]) continue;
			else
			{
				flag = 1;
				break;
			}
		}
		if(flag == 0)
		{
			specific.erase(specific.begin() + i);
			i--;
			cout << "Concept cannot be learned for animal class " + animal << endl;
		}
	}


	for(i = 0; i < generic.size(); i++)
	{
		flag = 0;
		for(j = 0; j < 16; j++)
		{
			if(generic[i][j] == "?" || generic[i][j] == input[j]) continue;
			else
			{
				flag = 1;
				break;
			}
		}
		// For hypothesis g in G that is not consistent with d, flag = 0
		if(flag == 0)
		{
			vector <string> hypothesis_being_removed(16);
			hypothesis_being_removed = generic[i];
			// Remove hypothesis g(inconsistant with data set) from G
			generic.erase(generic.begin() + i);
			i--;
			// Add to G all minimal generalizations of h
			for(j = 0; j < 16; j++)
			{
				if(hypothesis_being_removed[j] == "?")
				{
					if(j >= 0 && j <= 15 && j != 12)
					{
						vector <string> temp(16);
						if(input[j] == "1") temp[j] = "0";
						else if(input[j] == "0") temp[j] = "1";
						for(k = 0; k < 16; k++)
						{
							if(k != j)
								temp[k] = hypothesis_being_removed[k];
						}
						// Checking if some member of S is more specific than h(temp)
						// for(k = 0; k < 16; k++)
						// 	cout << temp[k] << " ";
						// cout << endl;
						flager = 0;
						// cout << "hello";
						for(k = 0; k < specific.size(); k++)
							if(more_general_than(temp, specific[k]) == 1) flager = 1;

						// cout << flager << endl;
						if(flager == 1)
						{
							// Checking if h(temp) is less general than any other hypothesis in G
							leave_loop = 0;
							for(k = 0; k < generic.size(); k++)
							{
								if(more_general_than(generic[k], temp) == 1)
								{
									// temp cannot be added to G
									leave_loop = 1;
									break;
								}
							}
							if(leave_loop == 1) continue;
							// Checking if h is more general than any other hypothesis in G
							for(k = 0; k < generic.size(); k++)
							{
								if(more_general_than(temp, generic[k]) == 1)
								{
									generic.erase(generic.begin() + k);
									k--;
								}
							}
							generic.push_back(temp);
						}
					}
					if(j == 12)
					{
						vector <string> temp1(16);
						vector <string> temp2(16);
						vector <string> temp3(16);
						vector <string> temp4(16);
						vector <string> temp5(16);
						if(input[j] == "0")
						{
							temp1[j] = "2";
							temp2[j] = "4";
							temp3[j] = "5";
							temp4[j] = "6";
							temp5[j] = "8";
						}
						if(input[j] == "2")
						{
							temp1[j] = "0";
							temp2[j] = "4";
							temp3[j] = "5";
							temp4[j] = "6";
							temp5[j] = "8";
						}
						if(input[j] == "4")
						{
							temp1[j] = "2";
							temp2[j] = "0";
							temp3[j] = "5";
							temp4[j] = "6";
							temp5[j] = "8";
						}
						if(input[j] == "5")
						{
							temp1[j] = "2";
							temp2[j] = "4";
							temp3[j] = "0";
							temp4[j] = "6";
							temp5[j] = "8";
						}
						if(input[j] == "6")
						{
							temp1[j] = "2";
							temp2[j] = "4";
							temp3[j] = "5";
							temp4[j] = "0";
							temp5[j] = "8";
						}
						if(input[j] == "8")
						{
							temp1[j] = "2";
							temp2[j] = "4";
							temp3[j] = "5";
							temp4[j] = "6";
							temp5[j] = "0";
						}
						for(k = 0; k < 16; k++)
						{
							if(k != j)
							{
								temp1[k] = hypothesis_being_removed[k];
								temp2[k] = hypothesis_being_removed[k];
								temp3[k] = hypothesis_being_removed[k];
								temp4[k] = hypothesis_being_removed[k];
								temp5[k] = hypothesis_being_removed[k];
							}
						}
						flager1 = 0;
						for(k = 0; k < specific.size(); k++)
							if(more_general_than(temp1, specific[k]) == 1) flager1 = 1;
						flager2 = 0;
						for(k = 0; k < specific.size(); k++)
							if(more_general_than(temp2, specific[k]) == 1) flager2 = 1;
						flager3 = 0;
						for(k = 0; k < specific.size(); k++)
							if(more_general_than(temp3, specific[k]) == 1) flager3 = 1;
						flager4 = 0;
						for(k = 0; k < specific.size(); k++)
							if(more_general_than(temp4, specific[k]) == 1) flager4 = 1;
						flager5 = 0;
						for(k = 0; k < specific.size(); k++)
							if(more_general_than(temp5, specific[k]) == 1) flager5 = 1;
						if(flager1 == 1)
						{
							// Checking if h(temp) is less general than any other hypothesis in G
							leave_loop1 = 0;
							for(k = 0; k < generic.size(); k++)
							{
								if(more_general_than(generic[k], temp1) == 1)
								{
									// temp cannot be added to G
									leave_loop1 = 1;
									break;
								}
							}
							if(leave_loop1 == 0)
							{
								// Checking if h is more general than any other hypothesis in G
								for(k = 0; k < generic.size(); k++)
								{
									if(more_general_than(temp1, generic[k]) == 1)
									{
										generic.erase(generic.begin() + k);
										k--;
									}
								}
								generic.push_back(temp1);
							}
						}
						if(flager2 == 1)
						{
							// Checking if h(temp) is less general than any other hypothesis in G
							leave_loop2 = 0;
							for(k = 0; k < generic.size(); k++)
							{
								if(more_general_than(generic[k], temp2) == 1)
								{
									// temp cannot be added to G
									leave_loop2 = 1;
									break;
								}
							}
							if(leave_loop2 == 0)
							{
								// Checking if h is more general than any other hypothesis in G
								for(k = 0; k < generic.size(); k++)
								{
									if(more_general_than(temp2, generic[k]) == 1)
									{
										generic.erase(generic.begin() + k);
										k--;
									}
								}
								generic.push_back(temp2);
							}
						}
						if(flager3 == 1)
						{
							// Checking if h(temp) is less general than any other hypothesis in G
							leave_loop3 = 0;
							for(k = 0; k < generic.size(); k++)
							{
								if(more_general_than(generic[k], temp3) == 1)
								{
									// temp cannot be added to G
									leave_loop3 = 1;
									break;
								}
							}
							if(leave_loop3 == 0)
							{
								// Checking if h is more general than any other hypothesis in G
								for(k = 0; k < generic.size(); k++)
								{
									if(more_general_than(temp3, generic[k]) == 1)
									{
										generic.erase(generic.begin() + k);
										k--;
									}
								}
								generic.push_back(temp3);
							}
						}
						if(flager4 == 1)
						{
							// Checking if h(temp) is less general than any other hypothesis in G
							leave_loop4 = 0;
							for(k = 0; k < generic.size(); k++)
							{
								if(more_general_than(generic[k], temp4) == 1)
								{
									// temp cannot be added to G
									leave_loop4 = 1;
									break;
								}
							}
							if(leave_loop4 == 0)
							{
								// Checking if h is more general than any other hypothesis in G
								for(k = 0; k < generic.size(); k++)
								{
									if(more_general_than(temp4, generic[k]) == 1)
									{
										generic.erase(generic.begin() + k);
										k--;
									}
								}
								generic.push_back(temp4);
							}
						}
						if(flager5 == 1)
						{
							// Checking if h(temp) is less general than any other hypothesis in G
							leave_loop5 = 0;
							for(k = 0; k < generic.size(); k++)
							{
								if(more_general_than(generic[k], temp5) == 1)
								{
									// temp cannot be added to G
									leave_loop5 = 1;
									break;
								}
							}
							if(leave_loop5 == 0)
							{
								// Checking if h is more general than any other hypothesis in G
								for(k = 0; k < generic.size(); k++)
								{
									if(more_general_than(temp5, generic[k]) == 1)
									{
										generic.erase(generic.begin() + k);
										k--;
									}
								}
								generic.push_back(temp5);
							}
						}
					}
				}
			}
			
		}
	}
}


int main()
{
	int i, j, k;

	// Initializing Generic and Specific hypothesis
	vector<string> most_general(16, "?");
	vector<string> most_specific(16, "-1");

	vector <vector<string> >generic1, generic2, generic3, generic4, generic5, generic6, generic7;
	vector <vector<string> >specific1, specific2, specific3, specific4, specific5, specific6, specific7;

	generic1.push_back(most_general);
	generic2.push_back(most_general);
	generic3.push_back(most_general);
	generic4.push_back(most_general);
	generic5.push_back(most_general);
	generic6.push_back(most_general);
	generic7.push_back(most_general);

	specific1.push_back(most_specific);
	specific2.push_back(most_specific);
	specific3.push_back(most_specific);
	specific4.push_back(most_specific);
	specific5.push_back(most_specific);
	specific6.push_back(most_specific);
	specific7.push_back(most_specific);


	ifstream infile("data.txt");
	ofstream fout;
	fout.open("assignment1_data.txt");
	// Reading file
	while (infile)
	{
		string s;
	    if (!getline( infile, s )) break;

	    istringstream ss( s );
	    vector <string> record;

	    while (ss)
	    {
	      string s;
	      if (!getline( ss, s, ',' )) break;
	      record.push_back( s );
	    }
		vector<string> input(17);
		for(i = 0; i < 17; i++)
		{
			input[i] = record[i+1];
			fout << input[i] << " ";
		}
		fout << endl;

		if(input[16] == "1")
		{
			positive("1", input, generic1, specific1);
			negative("2", input, generic2, specific2);
			negative("3", input, generic3, specific3);
			negative("4", input, generic4, specific4);
			negative("5", input, generic5, specific5);
			negative("6", input, generic6, specific6);
			negative("7", input, generic7, specific7);
		}
		if(input[16] == "2")
		{
			negative("1", input, generic1, specific1);
			positive("2", input, generic2, specific2);
			negative("3", input, generic3, specific3);
			negative("4", input, generic4, specific4);
			negative("5", input, generic5, specific5);
			negative("6", input, generic6, specific6);
			negative("7", input, generic7, specific7);
		}
		if(input[16] == "3")
		{
			negative("1", input, generic1, specific1);
			negative("2", input, generic2, specific2);
			positive("3", input, generic3, specific3);
			negative("4", input, generic4, specific4);
			negative("5", input, generic5, specific5);
			negative("6", input, generic6, specific6);
			negative("7", input, generic7, specific7);
		}
		if(input[16] == "4")
		{
			negative("1", input, generic1, specific1);
			negative("2", input, generic2, specific2);
			negative("3", input, generic3, specific3);
			positive("4", input, generic4, specific4);
			negative("5", input, generic5, specific5);
			negative("6", input, generic6, specific6);
			negative("7", input, generic7, specific7);
		}
		if(input[16] == "5")
		{
			negative("1", input, generic1, specific1);
			negative("2", input, generic2, specific2);
			negative("3", input, generic3, specific3);
			negative("4", input, generic4, specific4);
			positive("5", input, generic5, specific5);
			negative("6", input, generic6, specific6);
			negative("7", input, generic7, specific7);
		}
		if(input[16] == "6")
		{
			negative("1", input, generic1, specific1);
			negative("2", input, generic2, specific2);
			negative("3", input, generic3, specific3);
			negative("4", input, generic4, specific4);
			negative("5", input, generic5, specific5);
			positive("6", input, generic6, specific6);
			negative("7", input, generic7, specific7);
		}
		if(input[16] == "7")
		{
			negative("1", input, generic1, specific1);
			negative("2", input, generic2, specific2);
			negative("3", input, generic3, specific3);
			negative("4", input, generic4, specific4);
			negative("5", input, generic5, specific5);
			negative("6", input, generic6, specific6);
			positive("7", input, generic7, specific7);
		}
	}
	fout.close();

	// Printing results
	cout << "Generic boundary for animal 1 is: " << endl;
	for(i = 0; i < generic1.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << generic1[i][k] << " ";
		cout << endl;
	}
	cout << "Specific boundary for animal 1 is: " << endl;

	for(i = 0; i < specific1.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << specific1[i][k] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "Generic boundary for animal 2 is: " << endl;
	for(i = 0; i < generic2.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << generic2[i][k] << " ";
		cout << endl;
	}
	cout << "Specific boundary for animal 2 is: " << endl;

	for(i = 0; i < specific2.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << specific2[i][k] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "Generic boundary for animal 3 is: " << endl;
	for(i = 0; i < generic3.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << generic3[i][k] << " ";
		cout << endl;
	}
	cout << "Specific boundary for animal 3 is: " << endl;

	for(i = 0; i < specific3.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << specific3[i][k] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "Generic boundary for animal 4 is: " << endl;
	for(i = 0; i < generic4.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << generic4[i][k] << " ";
		cout << endl;
	}
	cout << "Specific boundary for animal 4 is: " << endl;

	for(i = 0; i < specific4.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << specific4[i][k] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "Generic boundary for animal 5 is: " << endl;
	for(i = 0; i < generic5.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << generic5[i][k] << " ";
		cout << endl;
	}
	cout << "Specific boundary for animal 5 is: " << endl;

	for(i = 0; i < specific5.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << specific5[i][k] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "Generic boundary for animal 6 is: " << endl;
	for(i = 0; i < generic6.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << generic6[i][k] << " ";
		cout << endl;
	}
	cout << "Specific boundary for animal 6 is: " << endl;

	for(i = 0; i < specific6.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << specific6[i][k] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "Generic boundary for animal 7 is: " << endl;
	for(i = 0; i < generic7.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << generic7[i][k] << " ";
		cout << endl;
	}
	cout << "Specific boundary for animal 7 is: " << endl;

	for(i = 0; i < specific7.size(); i++)
	{
		for(k = 0; k < 16; k++)
			cout << specific7[i][k] << " ";
		cout << endl;
	}
	cout << endl;
	return 0;
}

// Program ends