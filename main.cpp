#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

string grades[5] = {
    "HD",
    "D",
    "CR",
    "P",
    "F"};

int **progressData;
int nStudent;
int assesmentId;

bool isDataLoaded = false;

string scoreToGrade(int score)
{

  if (score >= 80 && score <= 100)
  {
    return "HD";
  }

  if (score >= 70 && score <= 79)
  {
    return "D";
  }

  if (score >= 60 && score <= 69)
  {
    return "CR";
  }

  if (score >= 50 && score <= 59)
  {
    return "P";
  }

  return "F";
}

int getGradeIndex(string grade)
{
  auto it = find(begin(grades), end(grades), grade);

  if (it == end(grades))
  {
    return -1;
  }

  return it - begin(grades);
}

string generateText(int **progressData, int nStudent, int assesmentId)
{

  string resultsData[5];

  for (int i = 0; i < nStudent; i++)
  {
    int score = progressData[i][assesmentId];
    resultsData[getGradeIndex(scoreToGrade(score))] += "*";
  }

  string text = "You have entered " + to_string(nStudent) + " students.\n";
  text += "Assesment " + to_string(assesmentId + 1) + " has been selected randomly.";
  text += "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

  for (int i = 0; i < 5; i++)
  {
    text += grades[i] + char(9) + ": " + resultsData[i] + "\n";
  }

  return text;
}

bool isValidScore(int score)
{
  return score >= 0 && score <= 100;
}

int **createList(string filename)
{
  int row = 100;
  int col = 10;

  int **progressData = new int *[row];

  ifstream inputfile(filename);

  if (!inputfile.is_open())
  {
    cout << "Error opening file.";
    return progressData;
  }

  for (int r = 0; r < row; r++)
  {
    progressData[r] = new int[col];
    for (int c = 0; c < col; c++)
    {
      int score;
      inputfile >> score;

      if (isValidScore(score))
      {
        progressData[r][c] = score;
      }
      else
      {
        cout << score << " is unrecognized";
      }
    }
  }

  inputfile.close();
  isDataLoaded = true;
  cout << "all data from " << filename << " are loaded.";

  return progressData;
}

void generateTable(int **progressData, int nStudent, int assesmentId)
{
  cout << generateText(progressData, nStudent, assesmentId);
}

void saveData(int **progressData, int nStudent, int assesmentId)
{
  cout << endl
       << "Do you want to save this data? (y/n): ";

  char wantSave;
  cin >> wantSave;
  cin.get();

  if (wantSave == 'y')
  {
    string text;

    ifstream ifile;
    ifile.open("savedProgressData.txt");
    if (!ifile)
    {
      text += ">> ALL SAVED STATISTICS << \n\n";
    }
    ifile.close();

    text += generateText(progressData, nStudent, assesmentId);
    ofstream file("savedProgressData.txt", ios_base::app);

    file << endl
         << endl
         << text;
    file.close();

    cout << "Data are successfully saved to savedProgressData.txt";
  }
}

void backToMenuPromt()
{
  cout << endl
       << "Back to main menu...";
  cin.get();
  system("CLS");
}

void option3()
{
  string filename;

  cout << "Please type the file name that you want to read" << endl;
  cout << "(leave blank to read the Results.txt file)" << endl
       << endl;
  cout << "file name: ";

  getline(cin, filename);

  if (filename.empty())
  {
    filename = "Results.txt";
  }

  progressData = createList(filename);

  backToMenuPromt();
}

void setNStudent()
{
CIN_STUDENT_NUMBER:
  cout << "How many students is class? (1-100): ";

  cin >> nStudent;
  cin.get();

  if (nStudent <= 0 || nStudent > 100)
  {
    cout << endl
         << "Invalid number, please try again" << endl;
    cin.get();
    goto CIN_STUDENT_NUMBER;
  }

  assesmentId = rand() % 10;
}

void option6()
{
  ifstream file("savedProgressData.txt");

  if (!file.is_open())
  {
    cout << "Please save result first by selecting option[5]";
  }
  else
  {
    cout << file.rdbuf();
  }
}

void runMenu()
{
DISPLAY_MENU:
  string menus[6] = {
      "End Testing the Program",
      "Display \"About\" Information",
      "Read and store data from files",
      "Generate a result Data Table",
      "Save Results Statistics to a file",
      "Display Results Statistics from a file"};

  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "    The Progress Statistics Generator" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  for (int i = 0; i < 6; i++)
  {
    cout << "[" << (i + 1) << "] " << menus[i] << endl;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "Which option would you like (1-6): ";

CIN_MENU:

  char choice;
  cin >> choice;
  cin.get();

  cout << endl;

  switch (choice)
  {
  case 49:
    cout << "Thank you for testing this application.";
    exit(EXIT_SUCCESS);
    break;

  case 50:
    /* code */
    break;

  case 51:
    option3();
    break;

  case 52:
    if (!isDataLoaded)
    {
      cout << "Please load data first by selecting option[3]";
    }
    else
    {
      setNStudent();
      generateTable(progressData, nStudent, assesmentId);
    }

    backToMenuPromt();
    break;
  case 53:
    if (!isDataLoaded)
    {
      cout << "Please load data first by selecting option[3]";
    }
    else
    {
      if (nStudent == 0)
      {
        setNStudent();
      }

      generateTable(progressData, nStudent, assesmentId);
      saveData(progressData, nStudent, assesmentId);
    }

    backToMenuPromt();
    break;
  case 54:
    option6();
    backToMenuPromt();
    break;

  default:
    cout << "invalid option, please type a number (1-6): ";
    goto CIN_MENU;
    break;
  }

  goto DISPLAY_MENU;
}

int main()
{
  runMenu();

  return 0;
}