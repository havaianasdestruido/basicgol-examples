/*
This code reads data from a CSV file, organizes that data
and answers basic facts based on the data. Data is related
to names of students and their marks in various subjects.

A simple CSV parser is implemented in a manner specific to
the student data. As an alternative, we can try using
open source CSV parsers.

In this code there are elements of sorting and searching,
handling dates and printing formatted tabular data.
*/

#include <basicgol.h>

#include <time.h>

//-----------------------------------------------------
// Types and Constants
//-----------------------------------------------------
// TODO Make this dynamic based on file content
// first_name,last_name,date_of_birth,sex,maths,sci,social,english,hindi,kannada
#define MAX_LINE_SIZE 1024
#define MAX_STUDENTS 300
#define NUM_COLS 10

ENUMERACAO(Subjects)
    Maths = 0,
    Science,
    Social,
    English,
    Hindi,
    Kannada,
    NumOfSubjects
FIM_ENUMERACAO(Subjects);

const CARACTERE *SubjNames[] = {
    "Maths", "Science", "Social", "English", "Hindi", "Kannada"
};

// A+ if >= 91, pass if >= 35
CARACTERE const * Grades[] = { "A+", "A", "B+", "B", "C", "D", "F" };
INTEIRO GradeCutOffs[]    = {  91,  81,  71,   61,  51,  35,   0  };

REGISTRO(Student)
    // Read from source
    CARACTERE first_name[50];
    CARACTERE last_name[50];
    CARACTERE date_of_birth[15];
    CARACTERE sex; // M or F
    INTEIRO marks[NumOfSubjects];

    // Computed
    INTEIRO total_marks;
    CARACTERE const * grades[NumOfSubjects];
    LOGICO has_passed;
FIM_REGISTRO(Student);

REGISTRO(Class)
    INTEIRO num_students;
    Student students[MAX_STUDENTS];
FIM_REGISTRO(Class);

//-----------------------------------------------------
// Helper Functions
//-----------------------------------------------------
FUNCAO REAL_CURTO diff_in_years(struct tm *a, struct tm *b) {
    RETORNE abs(b->tm_year*12 - a->tm_year*12 + b->tm_mon - a->tm_mon) / 12.0;
}

FUNCAO struct tm parse_date(const CARACTERE *date_str) {
    struct tm t = {0};
    INTEIRO day, month, year;

    SE sscanf(date_str, "%d/%d/%d", &day, &month, &year) == 3 ENTAO
        t.tm_mday = day;
        t.tm_mon = month - 1; // 0: Jan, 11: Dec
        t.tm_year = year - 1900;  // #years since 1900
    FIM_SE

    mktime(&t);
    RETORNE t;
}

PROCEDIMENTO parse_csv(Class *cls, const CARACTERE *filename) {
    FILE *fp = fopen(filename, "r");
    SE NAO fp ENTAO
        perror("Error opening file");
        RETORNE;
    FIM_SE

    CARACTERE line[MAX_LINE_SIZE];

    fgets(line, sizeof(line), fp); // ignore header row
    ENQUANTO fgets(line, sizeof(line), fp) FACA
        Student *s = cls->students + cls->num_students;

        // %[^,]: Matches any character except a comma (reads strings with spaces)
        INTEIRO matched = sscanf(line,
            "%[^,],%[^,],%[^,],%c,%d,%d,%d,%d,%d,%d",
            s->first_name, s->last_name, s->date_of_birth, &s->sex,
            &s->marks[Maths], &s->marks[Science], &s->marks[Social],
            &s->marks[English], &s->marks[Hindi], &s->marks[Kannada]);

        SE matched != NUM_COLS ENTAO
            ESCREVA_FMT("Warning: Row was malformed: %s\n", line);
        FIM_SE

        cls->num_students++;
    FIM_ENQUANTO

    fclose(fp);
}

FUNCAO CARACTERE const * get_grade(INTEIRO mark) {
    for (INTEIRO i = 0; i < TAMANHO_VETOR(GradeCutOffs); i++) {
        SE mark >= GradeCutOffs[i] ENTAO
            RETORNE Grades[i];
        FIM_SE
    }
    RETORNE "F"; // won't come here normally
}

FUNCAO LOGICO has_passed(CARACTERE const *grades[]) {
    INTEIRO j;
    PARA(j, 0, NumOfSubjects - 1) {
        // Overall failed if failed in at least one subject
        // Hence return false right away
        SE strcmp(grades[j], "F") == 0 ENTAO
            RETORNE FALSO;
        FIM_SE
    }
    RETORNE VERDADEIRO;
}

//-----------------------------------------------------
// Data Analysis
//-----------------------------------------------------
PROCEDIMENTO analyze_and_print(Class *cls) {
    INTEIRO i, j, g, k;
    // Process all students
    PARA(i, 0, cls->num_students - 1) {
        Student *s = cls->students + i;
        s->total_marks = 0;
        PARA(j, 0, NumOfSubjects - 1) {
            s->total_marks += s->marks[j];
            s->grades[j] = get_grade(s->marks[j]);
        }
        s->has_passed = has_passed(s->grades);
    }

    // Sex-wise count and average age
    ESCREVAL("-------------------------");
    ESCREVAL("        Count    Mean Age");
    ESCREVAL("-------------------------");
    INTEIRO num_m = 0, num_f = 0;
    REAL_CURTO age_m = 0, age_f = 0;
    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    mktime(today);
    PARA(i, 0, cls->num_students - 1) {
        struct tm dob = parse_date(cls->students[i].date_of_birth);
        REAL_CURTO age = diff_in_years(&dob, today);
        SE cls->students[i].sex == 'M' ENTAO
            num_m++;
            age_m += age;
        SENAO
            num_f++;
            age_f += age;
        FIM_SE
    }
    age_m /= num_m;
    age_f /= num_f;
    ESCREVA_FMT(" Boys      %2d       %4.2f\n", num_m, age_m);
    ESCREVA_FMT("Girls      %2d       %4.2f\n", num_f, age_f);
    ESCREVA_LINHA();

    // Subject-wise grade summary
    INTEIRO num_grades = TAMANHO_VETOR(Grades);
    ESCREVAL("--------------------------------------");
    ESCREVA(" Subject  ");
    PARA(g, 0, num_grades - 1) {
        ESCREVA_FMT("  %2s", Grades[g]);
    }
    ESCREVA_LINHA();
    ESCREVAL("--------------------------------------");
    PARA(j, 0, NumOfSubjects - 1) {
        ESCREVA_FMT("%8s  ", SubjNames[j]);
        INTEIRO count[num_grades];
        memset(count, 0, sizeof(count));
        PARA(i, 0, cls->num_students - 1) {
            CARACTERE const * grade = cls->students[i].grades[j];
            PARA(g, 0, num_grades - 1) {
                SE strcmp(grade, Grades[g]) == 0 ENTAO
                    count[g]++;
                    PARE;
                FIM_SE
            }
        }
        PARA(g, 0, num_grades - 1) {
            ESCREVA_FMT("  %2d", count[g]);
        }
        ESCREVA_LINHA();
    }
    ESCREVA_LINHA();

    // Subject-wise mean, min and max
    REAL_CURTO mean[NumOfSubjects];
    INTEIRO min[NumOfSubjects], max[NumOfSubjects];
    ESCREVAL("--------------------------------");
    ESCREVAL("Subject     Mean     Min     Max");
    ESCREVAL("--------------------------------");
    PARA(j, 0, NumOfSubjects - 1) {
        mean[j] = 0; min[j] = 100; max[j] = 0;
        PARA(i, 0, cls->num_students - 1) {
            INTEIRO mark = cls->students[i].marks[j];
            mean[j] += mark; // divide later
            SE mark < min[j] ENTAO
                min[j] = mark;
            FIM_SE
            SE mark > max[j] ENTAO
                max[j] = mark;
            FIM_SE
        }
        mean[j] /= (REAL_CURTO)cls->num_students;
        ESCREVA_FMT("%7s     %4.1f     %3d     %3d\n",
            SubjNames[j], mean[j], min[j], max[j]);
    }
    ESCREVA_LINHA();

    // Top 5 passing students by total marks
    // Inefficient sorting O(N^2)
    Student *toppers[5]; // sorted array of pointers
    ESCREVAL("---------------------------------------");
    ESCREVAL("#  Name                     Sex   Total");
    ESCREVAL("---------------------------------------");
    for (INTEIRO t = 0; t < TAMANHO_VETOR(toppers); t++) {
        INTEIRO high_total = 0; // t-th highest
        PARA(i, 0, cls->num_students - 1) {
            Student *s = cls->students + i;

            // Ignore failed students
            SE NAO s->has_passed ENTAO
                PROSSIGA;
            FIM_SE

            // Ignore students already in toppers
            LOGICO skip = FALSO;
            PARA(k, 0, t-1) {
                SE s == toppers[k] ENTAO
                    skip = VERDADEIRO;
                    PARE;
                FIM_SE
            }
            SE skip ENTAO
                PROSSIGA;
            FIM_SE

            SE s->total_marks > high_total ENTAO
                high_total = s->total_marks;
                toppers[t] = s;
            FIM_SE
        }
        CARACTERE name[20];
        snprintf(name, 20, "%s %s", toppers[t]->first_name, toppers[t]->last_name);
        ESCREVA_FMT("%d. %-21s    %3c   %5d\n",
            t+1, name, toppers[t]->sex, toppers[t]->total_marks);
    }
}

//-----------------------------------------------------
// Main
//-----------------------------------------------------
INICIO
    Class class12;
    parse_csv(&class12, "student_records.csv");
    analyze_and_print(&class12);
    RETORNE 0;
FIM
