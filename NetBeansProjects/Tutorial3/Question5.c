#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct{
    int student_id;
    int mark;
}grade;

double std_dev(grade *grades, double average, double number_students){
    double deviation = 0;
    for(int i = 0; i < number_students; i++){
        deviation += pow((grades[i].mark-average),2); 
    }
    deviation /= (number_students-1);
    deviation = sqrt(deviation);
    
    return deviation;
}

void grade_students(grade *grades, int num_students){
    int n_students = num_students;
    FILE *fp = fopen("grades.txt", "w");
    double sum = 0;
    double stdev=0;
    double avg=0;
    for(int i = 0; i < n_students; i++){
        sum += grades[i].mark;
    }
    avg = sum/n_students;
    stdev =  std_dev(grades, avg, n_students);
    
    fprintf(fp, "Average: %f\nStandard Deviation: %f\n\n", avg, stdev);
    fclose(fp);
}
    
int main(void){
    char *professor;
    grade *grades;
    int num_students=0;
    
    professor = (char *) calloc(256, sizeof(char));
    
    printf("Enter Professor's name: ");
    scanf("%s", professor);
    printf("Enter number of students to mark: ");
    scanf("%d", &num_students);
    
    grades = (grade *) malloc(sizeof(grade));
    
    for(int i = 0; i < num_students; i++){
        printf("Provide student ID: ");
        scanf("%d", &grades[i].student_id);
        printf("Provide mark: ");
        scanf("%d", &grades[i].mark);
    }
    
    grade_students(grades,num_students);
    
    
    free(professor);
    free(grades);
       
}