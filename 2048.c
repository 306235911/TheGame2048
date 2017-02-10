#include <stdio.h>
#include <stdlib.h>
#include <conio.h>；

void show();
void starUp();
int randomNum();
void transform(int aNum , int k);
int update();
int canMove(int side);
void moving(int side);
void mul(int side);
void newNum();
int vform(int i , int j);

int left = 9;
int right = 21;
int form[9][21];
int Num[15] ;
int score;

main()
{
    system("title 超级无敌最强2048");
    system("color D");
    starUp();
    show();
    while(1){
        while(update()){
            system("cls");
            newNum();
            show();
        }
    }
//    moving(4);
//    mul(4);
//    show();
}

void show()
{
    int i , j;

//    system("cls");
    for (i = 0 ; i < left ; i++){
        for ( j = 0 ; j < right ; j++){
            if ( i % 2 == 0)
                printf("-");
            else if( (j % 5 == 0) || (j == 0))
                printf("|");
            else if(form[i][j])
                printf("%d" , form[i][j]);
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("得分 %d ,那你好棒棒哦" , score);
}

void starUp()
{
    int rNum1 , rNum2;
//    int Num[15] ;
    int i , j;

    for (i = 1 ; i <= left ; i++){
        if (i % 2 != 0) //如果是边界的话就结束当前循环
            continue;
        for ( j = 1 ; j <= right ; j++){
            if ((j % 5 == 0) || (j == 1))
                continue; //如果是边界的话就结束当前循环
            else
                form[i][j] = 0;

        }
    }
    srand(time(NULL));
    rNum1 = rand()%17;
    srand(time(NULL));
    rNum2 = rand()%17;
    while ((rNum1 == 0) || (rNum2 == 0) || (rNum1 == rNum2)){
        rNum1 = rand()%17;
        rNum2 = rand()%17;
    }
    Num[rNum1-1] = randomNum();
    Num[rNum2-1] = randomNum();
    transform(Num[rNum1-1] , rNum1-1);
    transform(Num[rNum2-1] , rNum2-1);
//    form[1][4] =2;
//    form[1][9] = 2;
}

void transform(aNum ,k)  //日后可以重构
{
    int count;
    int x ,y ;

    if ( k%4 > 0)
        x = (k/4 +1)*2 -1;
    else
        x = (k/4)*2 -1;
    if (k %4 == 0)
        y = 16;
    else
        y = 1 + (((k%4)-1)* 5);
    if (aNum < 10)
        form[x][y+3] = aNum;
    else if((aNum > 10) && aNum < 100){
        form[x][y+2] = aNum/10;
        form[x][y+3] = aNum%10;
    }
    else if((aNum > 100) && aNum <1000){
        form[x][y+1] = aNum/100;
        form[x][y+2] = aNum/10;
        form[x][y+3] = aNum%10;
    }
    else{
        form[x][y] = aNum/1000;
        form[x][y+1] = aNum/100;
        form[x][y+2] = aNum/10;
        form[x][y+3] = aNum%10;
    }
}

int vform(int i , int j)
{
    int v;

    v = form[i][j] + form[i][j-1]*10 + form[i][j-2]*100 + form[i][j-3]*1000;
    return v;
}

int canMove(int side) //判断某个方向上能否进行移动
{
    int i , j;

    if (side == 1){ //如果是向上的话
        for (j=4; j<21 ; j=j+5){
            for (i = 1 ; i < 6 ; i=i+2){
                if (((form[i][j] ==0) && (form[i+2][j] != 0))) //|| ((form[i][j] == form[i+2][j]) &&(form[i][j] != 0)))
                    return 1;
                else if((vform(i,j)==vform(i+2,j)) && (form[i][j] != 0))
                    return 1;
            }
        }
        return 0;
    }
    else if(side == 2){
        for (j=4; j<21 ; j=j+5){
            for (i = 7 ; i > 1 ; i=i-2){ //从倒数第一行到正数第二行
                if (((form[i][j] ==0) && (form[i-2][j] != 0))) // || ((form[i][j] == form[i-2][j]) &&(form[i][j] != 0)))
                    return 1;
                else if((vform(i,j)==vform(i-2,j)) && (form[i][j] != 0))
                    return 1;
            }
        }
        return 0;
    }
    else if(side == 3){ //向左移动
        for (i=1 ; i<9 ; i=i+2){
            for ( j=4 ; j<15 ; j=j+5 ){
                if (((form[i][j] == 0) && (form[i][j+5] != 0))) // || ((form[i][j] == form[i][j+5]) &&(form[i][j] != 0)))
                    return 1;
                else if((vform(i,j)==vform(i,j+5)) && (form[i][j] != 0))
                    return 1;
            }
        }
        return 0;
    }
    else if (side == 4){
        for (i=1 ; i<9 ; i=i+2){
            for ( j=19 ; j>4 ; j=j-5 ){
                if (((form[i][j] == 0) && (form[i][j-5] != 0))) // || ((form[i][j] == form[i][j-5]) &&(form[i][j] != 0)))
                    return 1;
                else if((vform(i,j)==vform(i,j-5)) && (form[i][j] != 0))
                    return 1;
            }
        }
        return 0;
    }
}

void moving(int side)
{
    int i ,j , count ,k;
    int v;
    int c;

    if (side == 1){
        for (count = 0 ; count < 3 ; count++){
            for (j=4; j<21 ; j=j+5){
                for (i = 7 ; i > 1 ; i=i-2){ //从倒数第一行到正数第二行
                    if ((form[i][j] !=0) && (form[i-2][j] == 0)){
                        v = form[i][j] + form[i][j-1]*10 + form[i][j-2]*100 +form[i][j-3]*1000;
                        c = (((i-2)+1)/2 -1 )*4 + (j+1)/5;
                        transform(v,c);
                        for ( k=0 ; k<4 ;k++)
                            form[i][j-k] = 0;
                    }
                }
            }
        }
    }
    else if (side ==2 ){
        for (count = 0 ; count < 3 ; count++){
            for ( j=4 ; j<21 ; j=j+5){
                for ( i=1 ; i<7 ; i=i+2){
                    if (( form[i][j] != 0 ) && ( form[i+2][j]==0 )){
                        v = form[i][j] + form[i][j-1]*10 + form[i][j-2]*100 + form[i][j-3]*1000;
                        c = (((i+2)+1)/2 -1 )*4 + (j+1)/5;
                        transform(v,c);
                        for ( k=0 ; k<4 ;k++)
                            form[i][j-k] = 0;
                    }
                }
            }
        }
    }
    else if (side == 3){ //向左
        for (count = 0 ; count < 3 ; count++){
            for (i=1 ; i<8 ; i=i+2){
                for (j=19 ; j>4 ; j=j-5){
                    if ((form[i][j] != 0) && (form[i][j-5]==0)){
                        v = form[i][j] + form[i][j-1]*10 + form[i][j-2]*100 + form[i][j-3]*1000;
                        c = ((i+1)/2 -1 )*4 + (j+1-5)/5;
                        transform(v,c);
                        for ( k=0 ; k<4 ;k++)
                            form[i][j-k] = 0;
                    }
                }
            }
        }
    }
    else if (side == 4){
        for (count = 0 ; count < 3; count++){
            for (i=1 ; i<8 ; i=i+2){
                for ( j=4 ; j<15 ;j=j+5){
                    if ((form[i][j] != 0) &&(form[i][j+5]==0)){
                        v = form[i][j] + form[i][j-1]*10 + form[i][j-2]*100 + form[i][j-3]*1000;
                        c = ((i+1)/2 -1 )*4 + (j+1+5)/5;
                        transform(v,c);
                        for ( k=0 ; k<4 ;k++)
                            form[i][j-k] = 0;
                    }
                }
            }
        }
    }
}

void mul(int side)
{
    int i , j ,k;
    int v1 , v2;
    int c;
    int m;


    if (side == 1){
        for (j=4; j<21 ; j=j+5){
            for ( i=1 ; i<6 ; i=i+2){
                if ((form[i][j] != 0) && (form[i+2][j] != 0)){
                    v1 = form[i][j] + form[i][j-1]*10 + form[i][j-2]*100 + form[i][j-3]*1000;
                    v2 = form[i+2][j] + form[i+2][j-1]*10 + form[i+2][j-2]*100 + form[i+2][j-3]*1000;
                    if ((v1 == v2) && (v1!=0)){
                        v1 = v1*2;
                        c = ((i+1)/2 -1)*4 + (j+1)/5;
                        transform(v1,c);
                        for ( k=0 ; k<4 ;k++)
                            form[i+2][j-k] = 0;
                        score = score + v1;
                   }
                }
            }
        }
    }
    else if (side == 2){
        for ( j=4 ; j<21 ; j=j+5){
            for ( i=7 ; i>2 ; i=i-2){
                if ((form[i][j] != 0) && (form[i-2][j]!= 0)){
                    v1 = form[i][j] + form[i][j-1]*10 + form[i][j-2]*100 + form[i][j-3]*1000;
                    v2 = form[i-2][j] + form[i-2][j-1]*10 + form[i-2][j-2]*100 + form[i-2][j-3]*1000;
                    if ((v1==v2) && (v1!=0)){
                        v1 = v1*2;
                        c = ((i+1)/2 -1)*4 + (j+1)/5;
                        transform(v1,c);
                        for ( k=0 ; k<4 ;k++)
                            form[i-2][j-k] = 0;
                        score = score + v1;
                   }
                }
            }
        }
    }
    else if (side == 3){
        for (i=1 ; i<8 ; i=i+2){
            for ( j=4 ; j<15 ; j=j+5){
                if ((form[i][j] != 0) && (form[i][j+5] != 0)){
                    v1 = form[i][j] + form[i][j-1]*10 + form[i][j-2]*100 + form[i][j-3]*1000;
                    v2 = form[i][j+5] + form[i][j-1+5]*10 + form[i][j-2+5]*100 + form[i][j-3+5]*1000;
                    if ((v1==v2) && (v1!=0)){
                        v1 = v1*2;
                        c = ((i+1)/2 -1)*4 + (j+1)/5;
                        transform(v1,c);
                        for ( k=0 ; k<4 ;k++)
                            form[i][j+5-k] = 0;
                        score = score + v1;
                   }
                }
            }
        }
    }
    else if ( side==4 ){
        for ( i=1 ; i<8 ; i=i+2){
            for ( j=19 ; j>5 ; j=j-5){
                if ((form[i][j] != 0) && (form[i][j-5]!=0) ){
                    v1 = form[i][j] + form[i][j-1]*10 + form[i][j-2]*100 + form[i][j-3]*1000;
                    v2 = form[i][j-5] + form[i][j-1-5]*10 + form[i][j-2-5]*100 + form[i][j-3-5]*1000;
                    if ((v1==v2) && (v1!=0)){
                        v1 = v1*2;
                        c = ((i+1)/2 -1)*4 + (j+1)/5;
                        transform(v1,c);
                        for ( k=0 ; k<4 ;k++)
                            form[i][j-5-k] = 0;
                        score = score + v1;
                   }
                }
            }
        }
    }
}

int update()
{
    char input;
	if(kbhit()){  // 判断是否有输入
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		printf("%c" , input);
		if (input == 'w' && canMove(1)>0){
			moving(1);
			mul(1);
//            newNum();
			if (canMove(1)>0)
                moving(1);
		}
		else if (input == 's' && canMove(2)>0){
			moving(2);
			mul(2);
//            newNum();
			if (canMove(2)>0)
                moving(2);
		}
		else if (input == 'a' && canMove(3)>0){
			moving(3);
			mul(3);
//            newNum();
			if (canMove(3)>0)
                moving(3);
		}
		else if (input == 'd' && canMove(4)>0){
			moving(4);
			mul(4);
//            newNum();
			if (canMove(4)>0)
                moving(4);
		}
	    return 1;
	}

}

void newNum()
{
    int rNum;
    int i , j;

    srand(time(0));
    i = rand()%8;
    if (i%2 == 0)
        i++;
    j = rand()%4;
    if (j==0)
        j = 4;
    else if (j==1)
        j = 9;
    else if (j==2)
        j = 14;
    else if (j==3)
        j = 19;
    while (form[i][j] != 0){
        i = rand()%8;
        if (i%2 == 0)
            i++;
        j = rand()%4;
        if (j==0)
            j = 4;
        else if (j==1)
            j = 9;
        else if (j==2)
            j = 14;
        else if (j==3)
            j = 19;
    }
    form[i][j] = randomNum();
}

int randomNum()
{
    int rNum;

    srand(time(0));
    rNum = rand()%3;
    if ((rNum == 0) || (rNum == 1))
        return 2;
    else
        return 4;
}
