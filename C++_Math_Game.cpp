// بسم الله
#include <iostream>
#include <cstdlib>
using namespace std;

// =================== [ part 1 ] ===================

enum enQuestionLevel
{
    Easy = 1,
    Med,
    Hard,
    Mix
};

enum enOperationType
{
    Add = 1,
    Sub,
    Mul,
    Div,
    MixAll // <== I named this "MixAll" not "Mix" to not conflict with the var "Mix" that I've already declared the "enQuestionLevel" enum.
};

enum enResultStatus
{
    Pass = 1,
    Fail
};

struct stFinalResults // The results after finishing the game (all rounds).
{
    short questions_num = 0;
    string questions_level = "";
    string operation_type = "";
    short right_answers_num = 0;
    short wrong_answers_num = 0;
    enResultStatus result_status_num;
    string result_status_name = "";
};

short questions_num()
{
    short count = 0;
    do
    {
        cout << "\nHow many questions do you want to answer [1:10]? : ";
        cin >> count;
    } while (count < 1 || count > 10);

    return count;
}

enQuestionLevel question_level()
{
    short level = 0;
    do
    {
        cout << "Enter your question level ==> [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ";
        cin >> level;
    } while (level < 1 || level > 4);
    return (enQuestionLevel)level;
}

enOperationType operation_type()
{
    short type = 0;
    do
    {
        cout << "Enter an operation type ==> [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix ? ";
        cin >> type;
    } while (type < 1 || type > 5);
    return (enOperationType)type;
}

string level_choice(enQuestionLevel choice) // to know the name of any choice has been chosen
{
    string arr_level_choice[4] = {"Easy", "Medium", "Hard", "Mix"};
    return arr_level_choice[choice - 1];
}

string operation_type_choice(enOperationType choice)
{
    string operation_type_choice[5] = {"Addition", "Subtraction", "Multiplication", "Division", "Mix"};
    return operation_type_choice[choice - 1];
}

string get_result_status_name(enResultStatus choice)
{
    string result_status[2] = {"PASS", "FAIL"};
    return result_status[choice - 1];
}

void set_result_screen_color(enResultStatus status)
{
    switch (status)
    {
    case enResultStatus::Pass:
        system("color 2F"); // Green
        break;
    default:
        system("color 4F"); // Red
        cout << "\a";
        break;
    }
}

short random_num(short from, short to)
{
    short rand_num = rand() % (to - from + 1) + from;
    return rand_num;
}

void reset_terminal_screen()
{
    system("cls");
    system("color 0F");
}

string tabs(short num_of_tabs)
{
    string t = "";
    for (short i = 0; i < num_of_tabs; i++)
    {
        t += "\t";
    }
    return t;
}

// =================== [ part 2 ] ===================

char get_operator(enOperationType Operator)
{
    char arr_operators[4]{'+', '-', '*', '/'};
    switch (Operator)
    {
    case enOperationType::Add:
        return arr_operators[(enOperationType::Add)-1];
        break;
    case enOperationType::Sub:
        return arr_operators[(enOperationType::Sub)-1];
        break;
    case enOperationType::Mul:
        return arr_operators[(enOperationType::Mul)-1];
        break;
    case enOperationType::Div:
        return arr_operators[(enOperationType::Div)-1];
        break;
    default:
        return arr_operators[random_num(0, 3)];
        break;
    }
}

char print_and_get_each_question(short &num1, short &num2, enQuestionLevel Level, enOperationType Type)
{
    int result = 0;
    char myType = get_operator(Type);
    switch (Level)
    {
    case enQuestionLevel::Easy:
        num1 = random_num(1, 10);
        num2 = random_num(1, 10);
        cout << num1 << endl;
        cout << num2 << "  " << myType << endl;
        cout << "_____________________\n";
        return myType;
        break;
    case enQuestionLevel::Med:
        num1 = random_num(10, 50);
        num2 = random_num(10, 50);
        cout << num1 << endl;
        cout << num2 << "  " << myType << endl;
        cout << "_____________________\n";
        return myType;
        break;
    case enQuestionLevel::Hard:
        num1 = random_num(50, 100);
        num2 = random_num(50, 100);
        cout << num1 << endl;
        cout << num2 << "  " << myType << endl;
        cout << "_____________________\n";
        return myType;
        break;

    default:
        num1 = random_num(10, 500);
        num2 = random_num(1, 100);
        cout << num1 << endl;
        cout << num2 << "  " << myType << endl;
        cout << "_____________________\n";
        return myType;
        break;
    }
}

int get_math_result(short num1, short num2, char myType)
{
    switch (myType)
    {
    case '+':
        return num1 + num2;
        break;
    case '-':
        return num1 - num2;
        break;
    case '*':
        return num1 * num2;
        break;

    default:
        return num1 / num2;
        break;
    }
}

enResultStatus get_result_status_num(short right_answers_num, short wrong_answers_num)
{
    if (right_answers_num >= wrong_answers_num)
    {
        return enResultStatus::Pass;
    }
    return enResultStatus::Fail;
}

stFinalResults fill_final_results(short question_count, enQuestionLevel Level, enOperationType Type, short right_answers_num, short wrong_answers_num)
{
    stFinalResults FinalResults;
    FinalResults.questions_num = question_count;
    FinalResults.questions_level = level_choice(Level);
    FinalResults.operation_type = operation_type_choice(Type);
    FinalResults.right_answers_num = right_answers_num;
    FinalResults.wrong_answers_num = wrong_answers_num;
    FinalResults.result_status_num = get_result_status_num(right_answers_num, wrong_answers_num);
    FinalResults.result_status_name = get_result_status_name(FinalResults.result_status_num);
    return FinalResults;
}

stFinalResults play_the_game()
{
    stFinalResults FinalResult;
    short num1 = 0, num2 = 0, right_answers = 0, wrong_answers = 0, result = 0, correct_result = 0;
    char myType = 'M';
    int question_count = questions_num();
    enQuestionLevel Level = question_level();
    enOperationType OperationType = operation_type();
    for (int i = 0; i < question_count; i++)
    {
        cout << "\n\nQuestion [" << i + 1 << "/" << question_count << "]\n\n";
        myType = print_and_get_each_question(num1, num2, Level, OperationType);
        cin >> result;
        correct_result = get_math_result(num1, num2, myType);
        if (result == correct_result)
        {
            cout << "Right Answer :-)\n";
            set_result_screen_color(enResultStatus::Pass);
            right_answers++;
        }
        else
        {
            cout << "Wrong Answer :-(\n";
            cout << "Correct Answer = " << correct_result << endl;
            set_result_screen_color(enResultStatus::Fail);
            wrong_answers++;
        }
    }
    return fill_final_results(question_count, Level, OperationType, right_answers, wrong_answers);
}

void print_final_results(stFinalResults FinalResults)
{
    cout << tabs(6) << "___________________________________________________\n";
    cout << tabs(6) << "               Final Result is [" << FinalResults.result_status_name << "]\n";
    cout << tabs(6) << "___________________________________________________\n";
    cout << tabs(6) << "Number of Questions     : " << FinalResults.questions_num << endl;
    cout << tabs(6) << "Questions Level         : " << FinalResults.questions_level << endl;
    cout << tabs(6) << "Operation Type          : " << FinalResults.operation_type << endl;
    cout << tabs(6) << "Number of Right Answers : " << FinalResults.right_answers_num << endl;
    cout << tabs(6) << "Number of Wring Answers : " << FinalResults.wrong_answers_num << endl;
    cout << tabs(6) << "___________________________________________________\n";
    set_result_screen_color(FinalResults.result_status_num);
}

void start_the_game()
{
    char play_again = 'Y';
    do
    {
        reset_terminal_screen();
        stFinalResults FinalResults = play_the_game(); // to get the fill_final_results() func. the 2 have the same data type.
        print_final_results(FinalResults); // the FinalResults has been full with final game results, because of fill_final_results() func, which is as a return of the play_the_game func.
        cout << tabs(6) << "Do you want to play again? [Y/N] : ";
        cin >> play_again;
    } while (play_again == 'Y' || play_again == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    start_the_game();
    return 0;
}