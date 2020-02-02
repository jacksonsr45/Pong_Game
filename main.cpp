#include <iostream>
#include <time.h>
#include <conio.h>


using namespace std;

enum eDir {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3,
            RIGTH = 4, UPRIGHT= 5, DOWNRIGTH= 6};

class Ball
{
    private:
        int x, y;
        int dirX, dirY;
        eDir direction;
    public:
        Ball(int posX, int posY)
        {
            dirX = posX;
            dirY = posY;
            x = posX;
            y = posY;
            direction = STOP;
        }
    void Reset()
    {
        x = dirX;
        direction = STOP;
    }
    void Direction(eDir d)
    {
        direction = d;
    }
    void randDirection()
    {
        direction = (eDir)((rand() % 6) + 1);
    }
    inline int getX(){ return x; }
    inline int getY(){ return y; }
    inline eDir getDirection(){ return direction; }
    void Move()
    {
        switch (direction)
        {
        case STOP:
            break;
        case LEFT:
            x -= 1;
            break;
        case RIGTH:
            x += 1;
            break;
        case UPLEFT:
            x -= 1;
            y -= 1;
            break;
        case UPRIGHT:
            x += 1;
            y -= 1;
            break;
        case DOWNLEFT:
            x -= 1;
            y += 1;
            break;
        case DOWNRIGTH:
            x += 1;
            y += 1;
            break;
        default:
            break;
        }
    }
    friend ostream & operator<<(ostream & o, Ball c)
    {
        o << "Ball [" << c.x << "," << c.y << "]["
            << c.direction << "]";
        return o;
    }
};
class Paddle
{
    private:
        int x, y;
        int dirX, dirY;
    public:
        Paddle()
        {
            x = y = 0;
        }
        Paddle(int posX, int posY): Paddle()
        {
            dirX = posX;
            dirY = posY;
            x = posX;
            y = posY;
        }
    inline void Reset(){x = dirX; y = dirY; }
    inline int getX(){ return x; }
    inline int getY(){ return y; }
    inline void moveDown(){ y-= 1; }
    inline void moveUp(){ y+= 1; }
    friend ostream & operator<<(ostream & o, Paddle c)
    {
        o << "Paddle [" << c.x << "," << c.y << "]";
        return o;
    }

};
class  GameManger
{
private:
    int width, heigth;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    Ball *ball;
    Paddle *player1;
    Paddle *player2;
public:
    GameManger(int w, int h)
    {
        srand(time(NULL));
        quit = false;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        score1 = score2 = 0;
        width = w;
        heigth = h;
        ball = new Ball( w/ 2,h / 2);
        player1 = new Paddle( 2, h / 2 - 3);
        player2 = new Paddle( w - 1, h / 2 - 3);
    }
    ~GameManger()
    {
        delete ball, player1, player2;
    }
    void ScoreUp(Paddle * player)
    {
        if (player == player1)
        {
            score1 += 1;
        }
        else
        {
            score2 += 1;
        }
        ball->Reset();
        player1->Reset();
        player2->Reset();
    }
    void Draw()
    {
        system("cls");
        for (int i = 0; i < width + 2 ; i++)
        {
            cout << "\xB2";
        }
        cout << endl;
        
        for (int i = 0; i < heigth; i++)
        {
            for (int j = 0; j < width + 2; j++)
            {
                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = player1->getX();
                int player2x = player2->getX();
                int player1y = player1->getY();
                int player2y = player2->getY();
                
                if (j == 0)
                {
                    cout << "\xB2";
                }

                else if (ballx == j && bally == i)
                {   
                    cout << "O";
                }
                
                else if (player1x == j && player1y == i)
                {
                    cout << "\xDB";
                }
                else if (player1x == j && player1y + 1 == i)
                {
                    cout << "\xDB";
                }
                else if (player1x == j && player1y + 2 == i)
                {
                    cout << "\xDB";
                }
                else if (player1x == j && player1y + 3 == i)
                {
                    cout << "\xDB";
                }

                else if (player2x == j && player2y == i)
                {
                    cout << "\xDB";
                }
                else if (player2x == j && player2y + 1 == i)
                {
                    cout << "\xDB";
                }
                else if (player2x == j && player2y + 2 == i)
                {
                    cout << "\xDB";
                }
                else if (player2x == j && player2y + 3 == i)
                {
                    cout << "\xDB";
                }

                else
                {
                    cout << " ";
                }
                
                if (j == width)
                {
                    cout << "\xB2";
                }
            }   
            cout << endl;    
        }
        
        for (int i = 0; i < width + 2 ; i++)
        {
            cout << "\xB2";
        }
        cout << endl;

        cout << "SCORE 1:: " << score1 << " SCORE 2:: " << score2 << endl;
    }
    void Input()
    {
        ball->Move();
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        if (_kbhit())
        {
            char current = _getch();
            if (current == up1)
            {
                if (player1y > 0)
                {
                    player1->moveDown();
                }
            }
            if (current == up2)
            {
                if (player2y > 0)
                {
                    player2->moveDown();
                }
            }
            if (current == down1)
            {
                if (player1y + 4 < heigth)
                {
                    player1->moveUp();
                }
            }
            if (current == down2)
            {
                if (player2y + 4 < heigth)
                {
                    player2->moveUp();
                }
            }

            if(ball->getDirection() == STOP)
            {
                ball->randDirection();
            }
            
            if (current == 'q')
            {
                quit = true;
            }
        }
    }
    void Logic()
    {
        ball->Move();
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        for(int i = 0; i < 4; i++)
        {
            if(ballx == player1x +1)
            {
                if (bally == player1y + i)
                {
                    ball->Direction((eDir)((rand() % 3) + 4));
                }
            }
        }
        for(int i = 0; i < 4; i++)
        {
            if(ballx == player1x -1)
            {
                if (bally == player1y + i)
                {
                    ball->Direction((eDir)((rand() % 3) + 1));
                }
            }
        }

        if ( bally == heigth -1)
        {
            ball->Direction(ball->getDirection() == DOWNRIGTH ? UPRIGHT: UPLEFT);
        }
        if ( bally == 0)
        {
            ball->Direction(ball->getDirection() == UPRIGHT ? DOWNRIGTH: DOWNLEFT);
        }

        if ( ballx == width -1)
        {
            ScoreUp(player1);
        }
        if ( ballx == 0)
        {
            ScoreUp(player2);
        }
    }
    void Run()
    {
        while (!quit)
        {
            Draw();
            Input();
            Logic();
        }
    }
};

int main()
{
    GameManger c(40,20);
    c.Run();
    return 0;
}
