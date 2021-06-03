#include <graphics.h>
using namespace std;
void verificareCastig(int board[16][16],int &ok, int &gameEnd);
void drawBoard(int x1, int y1, int x2, int y2, int color);
void jocNou(int &ok,bool &computerPlay, int &pieceSet);///aici se desfasoara jocul in sine
void asteaptaClick(int &x, int &y);
void butoaneDupaTerminareaJocului(int &x, int &y, int &ok, bool &computerPlay, int &pieceSet);
void butoanePlusTablaDeJoc(int &x, int &y, int (&board)[16][16],bool &jucatorulUnu, bool &jucatorulDoi, int &ok, bool &computerPlay, int &pieceSet, int &gameEnd);
void verificareCastigSinglePlayer(int board[16][16],int &ok, int &gameEnd);
void drawMenu(bool &computerPlay);  ///prezinta pagina cu meniul principal
void choosePieces(int ok, bool &computerPlay);  ///prezinta pagina pe care se face alegerea setului de piese dorit
void computerPlayPutPiece(int (&board)[16][16],int &pieceSet, int &x, int &y);
void IJtoXY(int i,int j, int &x, int &y); ///transforma I sj J din matrice in coordonate X si Y;
///folosita pentru algoritmul de joc singleplayer si pentru trasarea liniei care arata cele 5 piese castigatoare
int rotunjireLa_25sau75(int x);   ///rotunjeste coordonatele returnate de clickul mouseului pentru a plasa piesa corect pe tabla de joc
int screenWidth=GetSystemMetrics(SM_CXSCREEN);
int screenHeight=GetSystemMetrics(SM_CYSCREEN);
int main()
{
    initwindow(screenWidth, screenHeight, "",-3,-3);
    bool computerPlay=false;
    drawMenu(computerPlay);
    return 0;
}
void drawMenu(bool &computerPlay)       ///au fost folosite imagini de tip .gif ca o alternativa la png, pentru se putea pastra transparenta imaginilor
{
    bool menu=true;
    int x=0,y=0;
    int ok=0;
    setactivepage(1);
    setvisualpage(1);
    readimagefile("imagini\\background.jpg",0,0,screenWidth,screenHeight);
    readimagefile("imagini\\cinci in linie.gif",618,100,1302,240);
    readimagefile("imagini\\singleplayer.gif",835,400,1085,467);
    readimagefile("imagini\\multiplayer.gif",797,500,1123,567);
    readimagefile("imagini\\quit.gif",885,600,1035,667);
    do
    {
        asteaptaClick(x,y);
        if(x>840 && x<1155 && y>400 && y<465)
        {
            computerPlay=true;
            menu=false;
            setactivepage(3);
            setvisualpage(3);
            choosePieces(ok,computerPlay);
        }
        else if(x>885 && x<1030 && y>600 && y<665)
        {
            menu=false;
            closegraph();
            exit(0);
            return;
        }
        else if(x>800 && x<1115 && y>500 && y<565)
        {
            computerPlay=false;
            menu=false;
            setactivepage(3);
            setvisualpage(3);
            choosePieces(ok,computerPlay);
        }
    }
    while(menu==true);
}
void choosePieces(int ok, bool &computerPlay)
{
    int pieceSet;
    int x,y;
    bool choosing=true;
    DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);
    readimagefile("imagini\\background.jpg",0,0,screenWidth,screenHeight);
    readimagefile("imagini\\chooseset.gif",765,100,1155,216);
    readimagefile("imagini\\sets.gif",385,200,1585,875);
    do
    {
        asteaptaClick(x,y);
        if(x>630 && x<760 && y>340 && y<720)
        {
            pieceSet=1;
            choosing=false;
            setactivepage(0);
            setvisualpage(0);
            jocNou(ok,computerPlay,pieceSet);
        }
        else if(x>785 && x<940 && y>340 && y<720)
        {
            pieceSet=2;
            choosing=false;
            setactivepage(0);
            setvisualpage(0);
            jocNou(ok,computerPlay,pieceSet);
        }
        else if(x>965 && x<1120 && y>340 && y<720)
        {
            pieceSet=3;
            choosing=false;
            setactivepage(0);
            setvisualpage(0);
            jocNou(ok,computerPlay,pieceSet);
        }
        else if(x>1160 && x<1300 && y>340 && y<720)
        {
            pieceSet=4;
            choosing=false;
            setactivepage(0);
            setvisualpage(0);
            jocNou(ok,computerPlay,pieceSet);
        }
    }
    while(choosing==true);
}
void asteaptaClick(int &x, int &y)
{
    bool gata;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            gata=true;
            delay(10);
        }
    }
    while(!gata);
}
void jocNou(int &ok, bool &computerPlay, int &pieceSet)
{
    int gameEnd=0;
    setactivepage(0);
    setvisualpage(0);
    DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);
    setbkcolor(BLACK);
    int color=15;
    cleardevice();
    readimagefile("imagini\\background.jpg",0,0,screenWidth,screenHeight);
    setlinestyle(0,1,1);
    drawBoard(100,100,850,850,color);
    int board[16][16]= {0};
    bool jucatorulUnu=true;
    bool jucatorulDoi=false;
    int x, y;
    settextstyle(TRIPLEX_FONT,0,0);
    setcolor(WHITE);
    readimagefile("imagini\\rules.gif",1000,50,1700,447);
    readimagefile("imagini\\restart.gif",1000,500,1184,567);
    readimagefile("imagini\\quit2.gif",1000,700,1145,767);
    readimagefile("imagini\\returntomenu.gif",1000,600,1287,667);

    while(gameEnd==0)   ///in acest while se desfasoara jocul in sine
    {
        verificareCastig(board,ok,gameEnd);
        if(ok==1)
            readimagefile("imagini\\won11.gif",200,20,710,88);
        else if (ok==2)
            readimagefile("imagini\\won22.gif",200,20,710,88);
        if(ok==0&&gameEnd==0)
        {
            asteaptaClick(x,y);
            butoanePlusTablaDeJoc(x,y,board,jucatorulUnu,jucatorulDoi,ok,computerPlay, pieceSet, gameEnd);
        }
    }
    delay(50);
    butoaneDupaTerminareaJocului(x,y,ok,computerPlay,pieceSet);
}
void butoaneDupaTerminareaJocului(int &x, int &y, int &ok, bool &computerPlay, int &pieceSet)
{
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(0);
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>1000 && x<1185 && y>500 && y<567)
        {
            ok=0;
            jocNou(ok,computerPlay,pieceSet);
        }
        else if(x>1000 && x<1145 && y>700 && y<767)
        {
            exit(0);
            closegraph();
            return;
        }
        else if(x>1000 && x<1287 && y>600 && y<667)
        {
            drawMenu(computerPlay);
            setvisualpage(1);
            setactivepage(1);
        }
    }
}
void butoanePlusTablaDeJoc(int &x, int &y, int (&board)[16][16],bool &jucatorulUnu, bool &jucatorulDoi, int &ok, bool &computerPlay, int &pieceSet, int &gameEnd)
{
    if(x<850 && y<850 && x>100 && y>100)
    {
        if((board[(y-100)/50+1][(x-100)/50+1])==0)
        {
            x=rotunjireLa_25sau75(x);
            y=rotunjireLa_25sau75(y);
            if(pieceSet==1)
            {
                if(computerPlay==true)
                {
                    board[(y-100)/50+1][(x-100)/50+1]=1;
                    readimagefile("imagini\\donut1.gif",x-23,y-23,x+23,y+23);
                    verificareCastigSinglePlayer(board,ok,gameEnd);
                    if(gameEnd==1)
                        return;
                    computerPlayPutPiece(board,pieceSet,x,y);
                    readimagefile("imagini\\donut2.gif",x-23,y-23,x+23,y+23);
                    verificareCastigSinglePlayer(board,ok,gameEnd);
                }
                else
                {
                    if(jucatorulDoi==true)
                    {
                        board[(y-100)/50+1][(x-100)/50+1]=2;
                        readimagefile("imagini\\donut2.gif",x-23,y-23,x+23,y+23);
                    }
                    else if (jucatorulUnu==true)
                    {
                        board[(y-100)/50+1][(x-100)/50+1]=1;
                        readimagefile("imagini\\donut1.gif",x-23,y-23,x+23,y+23);
                    }
                }
            }
            else if (pieceSet==2)
            {
                if(computerPlay==true)
                {
                    board[(y-100)/50+1][(x-100)/50+1]=1;
                    readimagefile("imagini\\sun.gif",x-23,y-23,x+23,y+23);
                    verificareCastigSinglePlayer(board,ok,gameEnd);
                    if(gameEnd==1)
                        return;
                    computerPlayPutPiece(board,pieceSet,x,y);
                    readimagefile("imagini\\moon.gif",x-23,y-23,x+23,y+23);
                    verificareCastigSinglePlayer(board,ok,gameEnd);
                }
                else
                {
                    if(jucatorulDoi==true)
                    {
                        board[(y-100)/50+1][(x-100)/50+1]=2;
                        readimagefile("imagini\\moon.gif",x-23,y-23,x+23,y+23);
                    }
                    else if (jucatorulUnu==true)
                    {
                        board[(y-100)/50+1][(x-100)/50+1]=1;
                        readimagefile("imagini\\sun.gif",x-23,y-23,x+23,y+23);
                    }
                }
            }
            else if (pieceSet==3)
            {
                if(computerPlay==true)
                {
                    board[(y-100)/50+1][(x-100)/50+1]=1;
                    readimagefile("imagini\\doctor.gif",x-23,y-23,x+23,y+23);
                    verificareCastigSinglePlayer(board,ok,gameEnd);
                    if(gameEnd==1)
                        return;
                    computerPlayPutPiece(board,pieceSet,x,y);
                    readimagefile("imagini\\virus.gif",x-23,y-23,x+23,y+23);
                    verificareCastigSinglePlayer(board,ok,gameEnd);
                }
                else
                {
                    if(jucatorulDoi==true)
                    {
                        board[(y-100)/50+1][(x-100)/50+1]=2;
                        readimagefile("imagini\\virus.gif",x-23,y-23,x+23,y+23);
                    }
                    else if (jucatorulUnu==true)
                    {
                        board[(y-100)/50+1][(x-100)/50+1]=1;
                        readimagefile("imagini\\doctor.gif",x-23,y-23,x+23,y+23);
                    }
                }
            }
            else if (pieceSet==4)
            {
                if(computerPlay==true)
                {
                    board[(y-100)/50+1][(x-100)/50+1]=1;
                    readimagefile("imagini\\angel.gif",x-23,y-23,x+23,y+23);
                    verificareCastigSinglePlayer(board,ok,gameEnd);
                    if(gameEnd==1)
                        return;
                    computerPlayPutPiece(board,pieceSet,x,y);
                    readimagefile("imagini\\evil.gif",x-23,y-23,x+23,y+23);
                    verificareCastigSinglePlayer(board,ok,gameEnd);
                }
                else
                {
                    if(jucatorulDoi==true)
                    {
                        board[(y-100)/50+1][(x-100)/50+1]=2;
                        readimagefile("imagini\\evil.gif",x-23,y-23,x+23,y+23);
                    }
                    else if (jucatorulUnu==true)
                    {
                        board[(y-100)/50+1][(x-100)/50+1]=1;
                        readimagefile("imagini\\angel.gif",x-23,y-23,x+23,y+23);
                    }
                }
            }
            if(jucatorulUnu==true)
            {
                jucatorulUnu=false;
                jucatorulDoi=true;
            }
            else if(jucatorulDoi==true)
            {
                jucatorulDoi=false;
                jucatorulUnu=true;
            }
        }
    }
    if(x>1000 && x<1185 && y>500 && y<567)
    {
        ok=0;
        jocNou(ok,computerPlay,pieceSet);
    }
    else if(x>1000 && x<1145 && y>700 && y<767)
    {
        exit(0);
        closegraph();
        return;
    }
    else if(x>1000 && x<1287 && y>600 && y<667)
    {
        drawMenu(computerPlay);
        setvisualpage(1);
        setactivepage(1);
    }
}
void IJtoXY(int i,int j, int &x, int &y)
{
    if(i==1&&j==1)
    {
        x=125;
        y=125;
    }
    else if(i==1&&j!=1)
    {
        x=125+50*(j-1);
        y=125;
    }
    else if(j==1&&i!=1)
    {
        x=125;
        y=125+50*(i-1);
    }
    else if(j!=1&&i!=1)
    {
        x=125+50*(j-1);
        y=125+50*(i-1);
    }
}
void verificareCastigSinglePlayer(int board[16][16],int &ok, int &gameEnd)
{
    verificareCastig(board,ok,gameEnd);
    if(ok==1)
    {
        readimagefile("imagini\\won11.gif",200,20,710,88);

        return;
    }
    else if (ok==2)
    {
        readimagefile("imagini\\won22.gif",200,20,710,88);
        return;
    }
}
void computerPlayPutPiece(int (&board)[16][16],int &pieceSet, int &x, int &y)
{
    delay(100);
    bool gasitLoc=false;
    int ok=0;
    x=0;
    y=0;
    for(int i=1; i<=15; i++)
    {
        for(int j=1; j<=15; j++)
        {
            if(ok==0)   ///daca variabila ok ramane 0 atunci cand algoritmul nu gaseste un loc potrivit pentru piesa.
            {           ///cand ok ramane 0, se va plasa o piesa pe un patratel liber, la intamplare

                if(board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==2&&board[i][j+3]==2&&board[i][j+4]==0)
                {
                    if(i<=15 && j<=11)
                    {
                        board[i][j+4]=2;
                        ok=1;
                        IJtoXY(i,j+4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==2&&board[i][j+3]==2&&board[i][j-1]==0)
                {
                    if(i<=15 && j<=15&&j>=2)
                    {
                        board[i][j-1]=2;
                        ok=1;
                        IJtoXY(i,j-1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==2&&board[i][j+3]==2&&board[i][j-1]==0)
                {
                    if(i<=15 && j<=15&&j>=2)
                    {
                        board[i][j-1]=2;
                        ok=1;
                        IJtoXY(i,j-1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j]==2&&board[i+2][j]==2&&board[i+3][j]==2&&board[i+4][j]==0)
                {
                    if(i<=11 && j<=15)
                    {
                        board[i+4][j]=2;
                        ok=1;
                        IJtoXY(i+4,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i-1][j]==2&&board[i-2][j]==2&&board[i-3][j]==2&&board[i-4][j]==0)
                {
                    if(i<=15 && j<=15&&i>=5)
                    {
                        board[i-4][j]=2;
                        ok=1;
                        IJtoXY(i-4,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i-1][j+1]==2&&board[i-2][j+2]==2&&board[i-3][j+3]==2&&board[i-4][j+4]==0)
                {
                    if(i<=15 && j<=11&&i>=5)
                    {
                        board[i-4][j+4]=2;
                        ok=1;
                        IJtoXY(i-4,j+4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j-1]==2&&board[i+2][j-2]==2&&board[i+3][j-3]==2&&board[i+4][j-4]==0)
                {
                    if(i<=11 && j<=15&&j>=5)
                    {
                        board[i+4][j-4]=2;
                        ok=1;
                        IJtoXY(i+4,j-4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i-1][j-1]==2&&board[i-2][j-2]==2&&board[i-3][j-3]==2&&board[i-4][j-4]==0)
                {
                    if(i<=15 && j<=15&&i>=5&&j>=5)
                    {
                        board[i-4][j-4]=2;
                        ok=1;
                        IJtoXY(i-4,j-4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&board[i+1][j+1]==2&&board[i+2][j+2]==2&&board[i+3][j+3]==2&&board[i+4][j+4]==0)
                {
                    if(i<=11 && j<=11)
                    {
                        board[i+4][j+4]=2;
                        ok=1;
                        IJtoXY(i+4,j+4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==2&&board[i][j+3]==2&&board[i][j-1]==0)
                {
                    if(i<=15 && j<=15&&j>=2)
                    {
                        board[i][j-1]=2;
                        ok=1;
                        IJtoXY(i,j-1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==2&&board[i][j+3]==2&&board[i][j+4]==0)
                {
                    if(i<=15 && j<=11)
                    {
                        board[i][j+4]=2;
                        ok=1;
                        IJtoXY(i,j+4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j+1]==2&&board[i+2][j+2]==0&&board[i+3][j+3]==2&&board[i+4][j+4]==2)
                {
                    if(i<=13 && j<=13)
                    {
                        board[i+2][j+2]=2;
                        ok=1;
                        IJtoXY(i+2,j+2,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j-1]==2&&board[i+2][j-2]==0&&board[i+3][j-3]==2&&board[i+4][j-4]==2)
                {
                    if(i<=13 && j<=15&&j>=3)
                    {
                        board[i+2][j-2]=2;
                        ok=1;
                        IJtoXY(i+2,j-2,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j]==2&&board[i+2][j]==0&&board[i+3][j]==2&&board[i+4][j]==2)
                {
                    if(i<=13 && j<=15)
                    {
                        board[i+2][j]=2;
                        ok=1;
                        IJtoXY(i+2,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&board[i+1][j+1]==1&&board[i+2][j+2]==1&&board[i+3][j+3]==1&&board[i+4][j+4]==0)
                {
                    if(i<=11 && j<=11)
                    {
                        ok=1;
                        board[i+4][j+4]=2;
                        IJtoXY(i+4,j+4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i-1][j+1]==1&&board[i-2][j+2]==1&&board[i-3][j+3]==1&&board[i-4][j+4]==0)
                {
                    if(i<=15 && j<=11 && i>=5)
                    {
                        ok=1;
                        board[i-4][j+4]=2;
                        IJtoXY(i-4,j+4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i-1][j-1]==1&&board[i-2][j-2]==1&&board[i-3][j-3]==1&&board[i-4][j-4]==0)
                {
                    if(i<=15 && j<=15 && j>=5 && i>=5)
                    {
                        ok=1;
                        board[i-4][j-4]=2;
                        IJtoXY(i-4,j-4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j-1]==1&&board[i+2][j-2]==1&&board[i+3][j-3]==1&&board[i+4][j-4]==0)
                {
                    if(i<=11 && j<=15 && j>=5)
                    {
                        ok=1;
                        board[i+4][j-4]=2;
                        IJtoXY(i+4,j-4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i][j+1]==1&&board[i][j+2]==1&&board[i][j+3]==1&&board[i][j+4]==0)
                {
                    if(i<=15 && j<=11)
                    {
                        ok=1;
                        board[i][j+4]=2;
                        IJtoXY(i,j+4,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i][j+1]==1&&board[i][j+2]==1&&board[i][j+3]==1&&board[i][j-1]==0)
                {
                    if(i<=15 && j<=15 && j>=2)
                    {
                        ok=1;
                        board[i][j-1]=2;
                        IJtoXY(i,j-1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j]==1&&board[i+2][j]==1&&board[i+3][j]==1&&board[i+4][j]==0)
                {
                    if(i<=11 && j<=15)
                    {
                        ok=1;
                        board[i+4][j]=2;
                        IJtoXY(i+4,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i-1][j]==1&&board[i-2][j]==1&&board[i-3][j]==1&&board[i-4][j]==0)
                {
                    if(i<=15 && j<=15 && i>=5)
                    {
                        ok=1;
                        board[i-4][j]=2;
                        IJtoXY(i-4,j,x,y);
                        return;
                    }
                }
                else if (board[i][j]==1&&board[i][j+1]==1&&board[i][j+2]==0&&board[i][j+3]==1&&board[i][j+4]==1)
                {
                    if(i<=15 && j<=13)
                    {
                        board[i][j+2]=2;
                        ok=1;
                        IJtoXY(i,j+2,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j]==1&&board[i+2][j]==0&&board[i+3][j]==1&&board[i+5][j]==1)
                {
                    if(i<=13 && j<=15)
                    {
                        board[i+2][j]=2;
                        ok=1;
                        IJtoXY(i+2,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j-1]==1&&board[i+2][j-2]==0&&board[i+3][j-3]==1&&board[i+4][j-4]==1)
                {
                    if(i<=13 && j<=15&&j>=3)
                    {
                        board[i+2][j-2]=2;
                        ok=1;
                        IJtoXY(i+2,j-2,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j+1]==1&&board[i+2][j+2]==0&&board[i+3][j+3]==1&&board[i+4][j+4]==1)
                {
                    if(i<=13 && j<=13)
                    {
                        board[i+2][j+2]=2;
                        ok=1;
                        IJtoXY(i+2,j+2,x,y);
                        return;
                    }
                }
                else if (board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==0&&board[i][j+3]==2&&board[i][j+4]==2)
                {
                    if(i<=15 && j<=13)
                    {
                        board[i][j+2]=2;
                        ok=1;
                        IJtoXY(i,j+2,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i][j+1]==0&&board[i][j+2]==2&&board[i][j+3]==2)
                {
                    if(i<=15 && j<=14)
                    {
                        board[i][j+1]=2;
                        ok=1;
                        IJtoXY(i,j+1,x,y);
                        return;
                    }
                }
                else if (board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==0&&board[i][j+3]==2)
                {
                    if(i<=15 && j<=13)
                    {
                        board[i][j+2]=2;
                        ok=1;
                        IJtoXY(i,j+2,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j]==0&&board[i+2][j]==2&&board[i+3][j]==2)
                {
                    if(i<=14 && j<=15)
                    {
                        board[i+1][j]=2;
                        ok=1;
                        IJtoXY(i+1,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j]==2&&board[i+2][j]==0&&board[i+3][j]==2)
                {
                    if(i<=13 && j<=15)
                    {
                        board[i+2][j]=2;
                        ok=1;
                        IJtoXY(i+2,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j-1]==2&&board[i+2][j-2]==0&&board[i+3][j-3]==2)
                {
                    if(i<=15 && j<=15&&j>=3)
                    {
                        board[i+2][j-2]=2;
                        ok=1;
                        IJtoXY(i+2,j-2,x,y);
                        return;
                    }
                }
                else if (board[i][j]==2&&board[i+1][j-1]==0&&board[i+2][j-2]==2&&board[i+3][j-3]==2)
                {
                    if(i<=14 && j<=15&&j>=2)
                    {
                        board[i+1][j-1]=2;
                        ok=1;
                        IJtoXY(i+1,j-1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j+1]==2&&board[i+2][j+2]==0&&board[i+3][j+3]==2)
                {
                    if(i<=13 && j<=13)
                    {
                        board[i+2][j+2]=2;
                        ok=1;
                        IJtoXY(i+2,j+2,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j+1]==0&&board[i+2][j+2]==2&&board[i+3][j+3]==2)
                {
                    if(i<=14 && j<=14)
                    {
                        board[i+1][j+1]=2;
                        ok=1;
                        IJtoXY(i+1,j+1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==2&&board[i][j-1]==0)
                {
                    if(i<=15 && j<=15&&j>=2)
                    {
                        ok=1;
                        IJtoXY(i,j-1,x,y);

                        board[i][j-1]=2;
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==2&&board[i][j+3]==0)
                {
                    if(i<=15 && j<=12)
                    {
                        board[i][j+3]=2;
                        ok=1;
                        IJtoXY(i,j+3,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j]==2&&board[i+2][j]==2&&board[i+3][j]==0)
                {
                    if(i<=12 && j<=15)
                    {
                        board[i+3][j]=2;
                        ok=1;
                        IJtoXY(i+3,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i-1][j]==2&&board[i-2][j]==2&&board[i-3][j]==0)
                {
                    if(i<=15 && j<=15&&j>=4)
                    {
                        board[i-3][j]=2;
                        ok=1;
                        IJtoXY(i-3,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i-1][j+1]==2&&board[i-2][j+2]==2&&board[i-3][j+3]==0)
                {
                    if(i<=15 && j<=12&&i>=4)
                    {
                        board[i-3][j+3]=2;
                        ok=1;
                        IJtoXY(i-3,j+3,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j-1]==2&&board[i+2][j-2]==2&&board[i+3][j-3]==0)
                {
                    if(i<=12 && j<=15&&j>=4)
                    {
                        board[i+3][j-3]=2;
                        ok=1;
                        IJtoXY(i+3,j-3,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i-1][j-1]==2&&board[i-2][j-2]==2&&board[i-3][j-3]==0)
                {
                    if(i<=15 && j<=15&&j>=4&&i>=4)
                    {
                        board[i-3][j-3]=2;
                        ok=1;
                        IJtoXY(i-3,j-3,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i+1][j+1]==2&&board[i+2][j+2]==2&&board[i+3][j+3]==0)
                {
                    if(i<=12 && j<=12)
                    {
                        board[i+3][j+3]=2;
                        ok=1;
                        IJtoXY(i+3,j+3,x,y);
                        return;
                    }
                }
                else if (board[i][j]==1&&board[i][j+1]==1&&board[i][j+2]==0&&board[i][j+3]==1)
                {
                    if(i<=15 && j<=13)
                    {
                        board[i][j+2]=2;
                        ok=1;
                        IJtoXY(i,j+2,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j]==0&&board[i+2][j]==1&&board[i+3][j]==1)
                {
                    if(i<=14 && j<=15)
                    {
                        board[i+1][j]=2;
                        ok=1;
                        IJtoXY(i+1,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j]==1&&board[i+2][j]==0&&board[i+3][j]==1)
                {
                    if(i<=13 && j<=15)
                    {
                        board[i+2][j]=2;
                        ok=1;
                        IJtoXY(i+2,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j-1]==1&&board[i+2][j-2]==0&&board[i+3][j-3]==1)
                {
                    if(i<=13 && j<=15&&j>=3)
                    {
                        board[i+2][j-2]=2;
                        ok=1;
                        IJtoXY(i+2,j-2,x,y);
                        return;
                    }
                }
                else if (board[i][j]==1&&board[i+1][j-1]==0&&board[i+2][j-2]==1&&board[i+3][j-3]==1)
                {
                    if(i<=14 && j<=15&&j>=2)
                    {
                        board[i+1][j-1]=2;
                        ok=1;
                        IJtoXY(i+1,j-1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j+1]==1&&board[i+2][j+2]==0&&board[i+3][j+3]==1)
                {
                    if(i<=13 && j<=13)
                    {
                        board[i+2][j+2]=2;
                        ok=1;
                        IJtoXY(i+2,j+2,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j+1]==0&&board[i+2][j+2]==1&&board[i+3][j+3]==1)
                {
                    if(i<=14 && j<=14)
                    {
                        board[i+1][j+1]=2;
                        ok=1;
                        IJtoXY(i+1,j+1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i][j+1]==1&&board[i][j+2]==1&&board[i][j+3]==0 )
                {
                    if(i<=15 && j<=12)
                    {
                        ok=1;
                        board[i][j+3]=2;
                        IJtoXY(i,j+3,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i][j+1]==1&&board[i][j+2]==1&&board[i][j-1]==0)
                {
                    if(i<=15 && j<=15 &&j>=2)
                    {
                        ok=1;
                        board[i][j-1]=2;
                        IJtoXY(i,j-1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j]==1&&board[i+2][j]==1&&board[i+3][j]==0)
                {
                    if(i<=12 && j<=15)
                    {
                        ok=1;
                        board[i+3][j]=2;
                        IJtoXY(i+3,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i-1][j]==1&&board[i-2][j]==1&&board[i-3][j]==0)
                {
                    if(i<=15 && j<=15 && i>=4)
                    {
                        ok=1;
                        board[i-3][j]=2;
                        IJtoXY(i-3,j,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i-1][j+1]==1&&board[i-2][j+2]==1&&board[i-3][j+3]==0)
                {
                    if(i<=15 && j<=12 && i>=4)
                    {
                        ok=1;
                        board[i-3][j+3]=2;
                        IJtoXY(i-3,j+3,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j-1]==1&&board[i+2][j-2]==1&&board[i-1][j+1]==0)
                {
                    if(i<=15 && j<=14 && i>=2)
                    {
                        ok=1;
                        board[i-1][j+1]=2;
                        IJtoXY(i-1,j+1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j+1]==1&&board[i+2][j+2]==1&&board[i-1][j-1]==0)
                {
                    if(i<=15 && j<=15 && i>=2 && j>=2)
                    {
                        ok=1;
                        board[i-1][j-1]=2;
                        IJtoXY(i-1,j-1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i-1][j-1]==1&&board[i-2][j-2]==1&&board[i-3][j-3]==0)
                {
                    if(i<=15 && j<=15 && i>=4 && j>=4)
                    {
                        ok=1;
                        board[i-3][j-3]=2;
                        IJtoXY(i-3,j-3,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&board[i+1][j+1]==1&&board[i+2][j+2]==1&&board[i+3][j+3]==0)
                {
                    if(i<=12 && j<=12)
                    {
                        ok=1;
                        board[i+3][j+3]=2;
                        IJtoXY(i+3,j+3,x,y);
                        return;
                    }
                }
                else if (board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==0)
                {
                    if(i<=15 && j<13)
                    {
                        board[i][j+2]=2;
                        ok=1;
                        IJtoXY(i,j+2,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i][j+1]==2&&board[i][j-1]==0)
                {
                    if(i<=15 && j<=15 &&j>=2)
                    {
                        board[i][j-1]=2;
                        ok=1;
                        IJtoXY(i,j-1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i][j+1]==0&&(board[i+1][j-1]==2&&board[i+1][j+1]==2 || board[i+1][j]==2))
                {
                    if(i<=15 && j<=14)
                    {
                        ok=1;
                        board[i][j+1]=2;
                        IJtoXY(i,j+1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==2&&board[i-2][j]==1&&board[i][j+1]==0)
                {
                    if(i<=15 && j<=14)
                    {
                        board[i][j+1]=2;
                        ok=1;
                        IJtoXY(i,j+1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j-1]==1&&board[i+2][j-2]==1&&board[i+3][j-3]==0 && (board[i-1][j+1]==1 ||board[i-1][j+1]==2) )
                {
                    if(i<=12 && j<=15 && j>=4)
                    {
                        ok=1;
                        board[i+3][j-3]=2;
                        IJtoXY(i+3,j-3,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j]==1&&board[i+2][j]==2&&board[i+1][j-1]==0)
                {

                    if(i<=14 && j<=15 && j>=2)
                    {
                        board[i+1][j-1]=2;
                        ok=1;
                        IJtoXY(i+1,j-1,x,y);
                        return;
                    }
                }
                else if(board[i][j]==1&&board[i+1][j]==0)
                {
                    if(i<=14 && j<=15)
                    {
                        board[i+1][j]=2;
                        ok=1;
                        IJtoXY(i+1,j,x,y);
                        return;
                    }
                }
            }
        }
    }
    if(ok==0)
    {
        while(gasitLoc==false)
        {
            int p=rand() % 15 + 1;
            int o=rand() % 15 + 1;
            if(board[p][o]==0)
            {
                int ok=1;
                board[p][o]=2;
                IJtoXY(p,o,x,y);
                gasitLoc=true;
                return;
            }
        }
    }
}
void verificareCastig(int board[16][16],int &ok,int &gameEnd)
{
    setcolor(0);
    int x1=0,y1=0;
    int x2=0,y2=0;
    for(int i=1; i<=15; i++)
        for(int j=1; j<=15; j++)
        {
            if(board[i][j]==1 && board[i][j+1]==1 && board[i][j+2]==1 && board[i][j+3]==1 && board[i][j+4]==1 || board[i][j]==2 && board[i][j+1]==2 && board[i][j+2]==2 && board[i][j+3]==2 && board[i][j+4]==2  )
            {
                setlinestyle(0,1,10);
                IJtoXY(i,j,x1,y1);
                IJtoXY(i,j+4,x2,y2);        ///pe langa actualizarea variabilei care determina daca jocul s-a incheiat sau nu
                line(x1,y1,x2-5,y2-5);      ///in aceste if-uri se traseaza linia care evidentiaza cele 5 piese castigatoare
                ok=board[i][j];
                gameEnd=1;
                return;
            }
            if(board[i][j]==1 && board[i][j-1]==1 &&board[i][j-2]==1 && board[i][j-3]==1 && board[i][j-4]==1 || board[i][j]==2 && board[i][j-1]==2 &&board[i][j-2]==2 && board[i][j-3]==2 && board[i][j-4]==2 )
            {
                setlinestyle(0,1,10);
                IJtoXY(i,j,x1,y1);
                IJtoXY(i,j-4,x2,y2);
                line(x1,y1,x2,y2);
                ok=board[i][j];
                gameEnd=1;
                return;
            }
            if(board[i][j]==1 && board[i+1][j]==1 && board[i+2][j]==1 && board[i+3][j]==1 && board[i+4][j]==1 || board[i][j]==2 && board[i+1][j]==2 && board[i+2][j]==2 && board[i+3][j]==2 && board[i+4][j]==2)
            {
                setlinestyle(0,1,10);
                IJtoXY(i,j,x1,y1);
                IJtoXY(i+4,j,x2,y2);
                line(x1,y1,x2,y2);
                ok=board[i][j];
                gameEnd=1;
                return;
            }
            if(board[i][j]==1 && board[i-1][j]==1 && board[i-2][j]==1 && board[i-3][j]==1 && board[i-4][j]==1 || board[i][j]==2 && board[i-1][j]==2 && board[i-2][j]==2 && board[i-3][j]==2 && board[i-4][j]==2)
            {
                setlinestyle(0,1,10);
                IJtoXY(i,j,x1,y1);
                IJtoXY(i-4,j,x2,y2);
                line(x1,y1,x2,y2);
                ok=board[i][j];
                gameEnd=1;
                return;
            }
            if(board[i][j]==1 && board[i-1][j+1]==1 && board[i-2][j+2]==1 && board[i-3][j+3]==1 && board[i-4][j+4]==1 || board[i][j]==2 && board[i-1][j+1]==2 && board[i-2][j+2]==2 && board[i-3][j+3]==2 && board[i-4][j+4]==2)
            {
                setlinestyle(0,1,10);
                IJtoXY(i,j,x1,y1);
                IJtoXY(i-4,j+4,x2,y2);
                line(x1,y1,x2,y2);
                ok=board[i][j];
                gameEnd=1;
                return;
            }
            if(board[i][j]==1 && board[i-1][j-1]== 1 && board[i-2][j-2]==1 && board[i-3][j-3]==1 && board[i-4][j-4]==1 || board[i][j]==2 && board[i-1][j-1]== 2 && board[i-2][j-2]==2 && board[i-3][j-3]==2 && board[i-4][j-4]==2)
            {
                setlinestyle(0,1,10);
                IJtoXY(i,j,x1,y1);
                IJtoXY(i-4,j-4,x2,y2);
                line(x1,y1,x2,y2);
                ok=board[i][j];
                gameEnd=1;
                return;
            }
            if(board[i][j]==1 && board[i+1][j-1]==1 && board[i+2][j-2]==1 && board[i+3][j-3]==1 && board[i+4][j-4]==1 || board[i][j]==2 && board[i+1][j-1]==2 && board[i+2][j-2]==2 && board[i+3][j-3]==2 && board[i+4][j-4]==2)
            {
                setlinestyle(0,1,10);
                IJtoXY(i,j,x1,y1);
                IJtoXY(i+4,j-4,x2,y2);
                line(x1,y1,x2,y2);
                ok=board[i][j];
                gameEnd=1;
                return;
            }
            if(board[i][j]==1 && board[i+1][j+1]==1 &&board[i+2][j+2]==1 && board[i+3][j+3]==1 && board[i+4][j+4]==1 || board[i][j]==2 && board[i+1][j+1]==2 &&board[i+2][j+2]==2 && board[i+3][j+3]==2 && board[i+4][j+4]==2)
            {
                setlinestyle(0,1,10);
                IJtoXY(i,j,x1,y1);
                IJtoXY(i+4,j+4,x2,y2);
                line(x1,y1,x2,y2);
                ok=board[i][j];
                gameEnd=1;
                return;
            }
        }
}
int rotunjireLa_25sau75(int x)
{
    int prima=x/100;
    int ult2=x%100;
    if(abs(ult2-25)<abs(75-ult2))
        ult2=25;
    else ult2=75;
    return prima*100+ult2;
}
void drawBoard(int x1, int y1, int x2, int y2,int color)
{
    setcolor(WHITE);
    int linii=15;
    int coloane=15;
    setlinestyle(0,1,4);
    for (int i=x1; i<=x2; i=i+(x2-x1)/linii)
        line(x1,i,x2,i);
    for (int j=y1; j<=y2; j=j+(y2-y1)/coloane)
        line(j,y1,j,y2);
}
