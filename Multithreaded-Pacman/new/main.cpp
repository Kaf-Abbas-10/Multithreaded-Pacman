#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include <array>
#include<cmath>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
using namespace sf;
using namespace std;


const int GRID_WIDTH = 23;
const int GRID_HEIGHT = 23;
const int CELL_SIZE = 20;
const float PACMAN_RADIUS = 9.96f;
const float PACMAN_SPEED = 50.0f; 
int MAX_PELLETS=5;
int pelletsEaten=0;
    RenderWindow window(VideoMode(GRID_WIDTH * CELL_SIZE, (GRID_HEIGHT * CELL_SIZE)+100), "SFML Pac-Man Maze");

    sf::SoundBuffer b;
    sf::Sound s;
// Define the maze with 1s as walls, 0s as paths, 2s as pellets, and 3s as mut pellets
int grid[GRID_HEIGHT][GRID_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1},
    {1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1},
    {1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2},
    {1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1},
    {1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


class Menu{
    public:
    bool flag2,flag1,exit;
    string name;
    int select_x,select_y;
    //add menu attributes here
    Menu()
    {
    select_x=select_y=0;
    exit=false;
    flag2=true;
    flag1=false;
    //constructors body
    }

    void display_menu(RenderWindow &win)

    {
    	Texture obj1,obj2,obj3,obj4;
        obj1.loadFromFile("img/menu1.png");
        obj2.loadFromFile("img/menu2.png");
        obj3.loadFromFile("img/menu3.png");
        obj4.loadFromFile("img/menu4.png");
        Sprite background(obj1);
    	background.setScale(1.5,1.2);
    	Event evnt;
    	while(true)
    	{
    		while(win.pollEvent(evnt))
    		{
            
    			if(Keyboard::isKeyPressed(Keyboard::Up)){
    				if(select_y==1)
    					select_y--;
    			}
    			else if(Keyboard::isKeyPressed(Keyboard::Down)){
    				if(select_y==0)
    					select_y++;
    			}
    			else if(Keyboard::isKeyPressed(Keyboard::Left)){
    				if(select_x==1)
    					select_x--;
    			}
    			else if(Keyboard::isKeyPressed(Keyboard::Right)){
    				if(select_x==0)
    					select_x++;
    			}
    			else if(Keyboard::isKeyPressed(Keyboard::Enter)){
    				if(select_x==0&&select_y==0){
                        return;
    				}
    				else if(select_x==1&&select_y==1){
    					std::exit(1);
    				}
    
    			}
    		if(select_x==0&&select_y==0)
    			background.setTexture(obj1);
    		else if(select_x==1&&select_y==0)
    			background.setTexture(obj2);
    		else if(select_x==0&&select_y==1)
    			background.setTexture(obj3);
    		else if(select_x==1&&select_y==1)
    			background.setTexture(obj4);
    		win.clear(Color::White);
            	win.draw(background);
            	win.display();
    		}
        } 
    }
};

class Pacman {
public:
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f nextDirection;  // Buffered next direction
    sf::Vector2f currentDirection;
    sf::IntRect pacManOpenMouth;
    Texture texture;

    Pacman(float startX, float startY) {
        pacManOpenMouth.left=150;pacManOpenMouth.top=0;pacManOpenMouth.width=15;pacManOpenMouth.height=15;
        texture.loadFromFile("/home/kaf/Desktop/new/things.png");
        position = sf::Vector2f(startX * CELL_SIZE + CELL_SIZE / 2, startY * CELL_SIZE + CELL_SIZE / 2);
        sprite.setScale(1.33333333f,1.33333333f);
        sprite.setPosition(position - sf::Vector2f(PACMAN_RADIUS, PACMAN_RADIUS));
        sprite.setTexture(texture);
        sprite.setTextureRect(pacManOpenMouth);
        velocity = sf::Vector2f(0, 0);  // Initially no movement
        nextDirection = sf::Vector2f(0, 0);  // Initially no buffered direction
        currentDirection = sf::Vector2f(0, 0);  // Initially no buffered direction
    }

    void update(float dt) {
    // Check if we can move in the next buffered direction
    sf::Vector2f proposedNewDirectionPosition = position + nextDirection * PACMAN_SPEED * dt;
    if (nextDirection != sf::Vector2f(0, 0) && canMoveTo(proposedNewDirectionPosition)) {
        velocity = nextDirection * PACMAN_SPEED;  // Change to the new direction
        currentDirection = nextDirection;  // Update current direction
        nextDirection = sf::Vector2f(0, 0);  // Clear the buffer
    }

    // Calculate new position based on current velocity
    sf::Vector2f newPosition = position + velocity * dt;
    if (!canMoveTo(newPosition)) {
        if (currentDirection != sf::Vector2f(0, 0)) {
            // Try to continue in the current direction if not directly blocked
            sf::Vector2f continueCurrentDirectionPosition = position + currentDirection * PACMAN_SPEED * dt;
            if (!canMoveTo(continueCurrentDirectionPosition)) {
                velocity = sf::Vector2f(0, 0);  // Only stop if the current path is blocked
            }
        } else {
            velocity = sf::Vector2f(0, 0);  // No current direction, so stop
        }
    } else {
        position = newPosition;  // Update position as normal
    }

    sprite.setPosition(position - sf::Vector2f(PACMAN_RADIUS, PACMAN_RADIUS));
}




    bool canMoveTo(const sf::Vector2f& proposedPosition) {
        // Check four corners of the bounding box for the proposed position
        std::array<sf::Vector2i, 4> points = {
            sf::Vector2i(proposedPosition.x - PACMAN_RADIUS, proposedPosition.y - PACMAN_RADIUS),
            sf::Vector2i(proposedPosition.x + PACMAN_RADIUS, proposedPosition.y - PACMAN_RADIUS),
            sf::Vector2i(proposedPosition.x - PACMAN_RADIUS, proposedPosition.y + PACMAN_RADIUS),
            sf::Vector2i(proposedPosition.x + PACMAN_RADIUS, proposedPosition.y + PACMAN_RADIUS)
        };

        for (auto& point : points) {
            int gridX = point.x / CELL_SIZE;
            int gridY = point.y / CELL_SIZE;
            if (gridY >= 0 && gridY < GRID_HEIGHT && gridX >= 0 && gridX < GRID_WIDTH && grid[gridY][gridX] == 1) {
                return false;  // Collision detected
            }
        }
        return true;  // No collision
    }

    void setDirection(const sf::Vector2f& dir) {
        nextDirection = dir;  // Buffer the direction first
    }
    
    void transition(){
        if(position.x<0)
            position.x=460;
        else if(position.x>460)
            position.x=0;
    }
};

class Ghost{
public:
    Sprite sprite;
    Texture text;
    Ghost(){};
    void set(Texture t,int x,int y){
        text=t;
        sprite.setTexture(text);
        sprite.setPosition(x*CELL_SIZE,y*CELL_SIZE);
    }

};

//Characters
Pacman pacman(7,9);
IntRect gh1;
IntRect gh2;
IntRect gh3;
IntRect gh4;
Texture g1;
Texture g2;
Texture g3;
Texture g4;
//Characters

const int NUM_GHOSTS = 4;
const int NUM_KEYS = 2;
const int NUM_PERMITS = 2;
bool permission[NUM_GHOSTS]={1,1,1,1};
Ghost ghosts[NUM_GHOSTS];
int pellets = 0;
bool power=false;

sem_t keys;
sem_t permits;


int score=-10,liveCount=3;
Text scores;
Font font;
Texture liveText;
Sprite lives[3];


void* UserInterface(void * arg){
    while(1){
        string text1="Score:";
        text1+=to_string(score);
        scores.setString(text1);
    }
}

sem_t writes,reads;
int readCount=0;

void eating(){
    int x,y;
    x=round(pacman.position.x)/CELL_SIZE;
    y=round(pacman.position.y)/CELL_SIZE;
    if(grid[y][x]==2){
        grid[y][x]=0;
        score+=10;
        //s.play();
        pelletsEaten++;
    }
}

void* writers(void* args){
    while(1){
        sem_wait(&writes);
        eating();
        sem_post(&writes);
    }
}

bool movingState[4];

void* movement1(void* args){
    if(movingState[0]){
    while(1){
        sem_wait(&reads);
        readCount++;
        if(readCount>0)
            sem_wait(&writes);
        sem_post(&reads);
        //movement
        //ghosts[0]
    // {
    //     int x,y;
    //     x = ghosts[0].sprite.getPosition().x;
    //     y = ghosts[0].sprite.getPosition().y;
    //     cout<<"Ghost x pos :"<<x<<"\n";
    //     cout<<"Ghost y pos :"<<y<<"\n";
    //     if(x/CELL_SIZE<15&&x/CELL_SIZE>10&&y/CELL_SIZE==9){
    //     cout<<":Kalkhfakjhd:"<<endl;
    //         ghosts[0].sprite.move(0.01f,0);
    //     }

    //     else if(x/CELL_SIZE==14&&y/CELL_SIZE==18){
    //         ghosts[0].sprite.move(0.01f,-0.01f);
    //     // ghosts[0].sprite.setPosition(15*CELL_SIZE,17*CELL_SIZE);
    //     }
    //     else if(x/CELL_SIZE<=17&&x/CELL_SIZE>=15&&y/CELL_SIZE==18){
    //         ghosts[0].sprite.move(-0.01f,0);
    //     }
    //     else if(x/CELL_SIZE==15&&y/CELL_SIZE>2&&y/CELL_SIZE<18){
    //         ghosts[0].sprite.move(0,-0.01f);
    //         cout<<1;
    //     }
    //     else if(x/CELL_SIZE<17&&x/CELL_SIZE>14&&y/CELL_SIZE==2){
    //         ghosts[0].sprite.move(0.01f,0);
    //     }
    //     else if(x/CELL_SIZE==17&&y/CELL_SIZE>0&&y/CELL_SIZE<=3){
    //         ghosts[0].sprite.move(0,-0.01f);
    //     }
    //     else if(x/CELL_SIZE>4&&y/CELL_SIZE==0){
    //         ghosts[0].sprite.move(-0.01f,0);
    //     }
    //     else if(x/CELL_SIZE==4&&y/CELL_SIZE>=0&&y/CELL_SIZE<3){
    //         ghosts[0].sprite.move(0,0.01f);
    //     }
    //     else if(x/CELL_SIZE<7&&x/CELL_SIZE>=4&&y/CELL_SIZE==3){
    //         ghosts[0].sprite.move(0.01f,0);
    //     }
    //     else if(x/CELL_SIZE==7&&y/CELL_SIZE>=3&&y/CELL_SIZE<19){
    //         ghosts[0].sprite.move(0,0.01f);
    //     }
    //     else if(x/CELL_SIZE>4&&x/CELL_SIZE<=7&&y/CELL_SIZE==19){
    //         ghosts[0].sprite.move(-0.01f,0);
    //     }
    //     else if(x/CELL_SIZE==4&&y/CELL_SIZE>=19&&y/CELL_SIZE<21){
    //         ghosts[0].sprite.move(0,0.01f);
    //     }
    //     else if(x/CELL_SIZE<17&&x/CELL_SIZE>=4&&y/CELL_SIZE==21){
    //         ghosts[0].sprite.move(0.01f,0);
    //     }
    //     else if(x/CELL_SIZE==17&&y/CELL_SIZE>18&&y/CELL_SIZE<=21){
    //         ghosts[0].sprite.move(0,-0.01f);
    //     }
        
    // }

        sem_wait(&reads);
        readCount--;

        if(readCount==0)
            sem_post(&writes);
        sem_post(&reads);
        sleep(10);
        if(1)//collisionCheck
            break;
    }
    }
    movingState[0]=false;
    permission[0]=false;
    ghosts[0].sprite.setPosition(9*CELL_SIZE,11*CELL_SIZE);
}



void* movement2(void* args) {
    if(movingState[1]){
    while(1){
        sem_wait(&reads);
        readCount++;
        if(readCount>0)
            sem_wait(&writes);
        sem_post(&reads);
        //movement

        sem_wait(&reads);
        readCount--;

        if(readCount==0)
            sem_post(&writes);
        sem_post(&reads);
        sleep(10);
        if(1)//collisionCheck
            break;
    }
    }
    movingState[1]=false;
    permission[1]=false;
    ghosts[1].sprite.setPosition(10*CELL_SIZE,11*CELL_SIZE);
}

void *movement3(void *args){
    if(movingState[2]){
    while(1){
        sem_wait(&reads);
        readCount++;
        if(readCount>0)
            sem_wait(&writes);
        sem_post(&reads);
        //movement
        //ghosts[2]
        

        sem_wait(&reads);
        readCount--;

        if(readCount==0)
            sem_post(&writes);
        sem_post(&reads);
        sleep(10);
        if(1)//collisionCheck
            break;
    }
    }
    movingState[2]=false;
    permission[2]=false;
    ghosts[2].sprite.setPosition(12*CELL_SIZE,11*CELL_SIZE);
}

void* movement4(void * args){
    if(movingState[3]){
    while(1){
        sem_wait(&reads);
        readCount++;
        if(readCount>0)
            sem_wait(&writes);
        sem_post(&reads);
        //movement
        //ghosts[3]
        
        sem_wait(&reads);
        readCount--;

        if(readCount==0)
            sem_post(&writes);
        sem_post(&reads);
        sleep(10);
        if(1)//collisionCheck
            break;
    }
    }
    movingState[3]=false;
    permission[3]=false;
    ghosts[3].sprite.setPosition(13*CELL_SIZE,11*CELL_SIZE);
}


void moves(int ghostNo){
    //cout<<"Ghost"<<ghostNo;
    switch (ghostNo){
        case 0:
            ghosts[ghostNo].sprite.setPosition(9*CELL_SIZE,9*CELL_SIZE);
            movingState[0]=true;
            break;
        case 1:
            ghosts[ghostNo].sprite.setPosition(10*CELL_SIZE,9*CELL_SIZE);
            movingState[1]=true;
            break;
        case 2:
            ghosts[ghostNo].sprite.setPosition(12*CELL_SIZE,9*CELL_SIZE);
            movingState[2]=true;
            break;
        case 3:
            ghosts[ghostNo].sprite.setPosition(13*CELL_SIZE,9*CELL_SIZE);
            movingState[3]=true;
            break;
    }
}

void* ghost(void* arg) {
    int id = *((int*)arg);
    int key = id % NUM_KEYS;
    int permit = id % NUM_PERMITS;

    
    sem_wait(&keys);
    sem_wait(&permits);
    cout<<id<<endl;
    moves(id-1);
    while(movingState[id-1]){
    }
    sem_post(&permits);
    sem_post(&keys);
    

}


void pelletEater(){
    Clock c;
    while(1){
        if(!power){
            int x,y;
            x=round(pacman.position.x)/CELL_SIZE;
            y=round(pacman.position.y)/CELL_SIZE;
            if(grid[y][x]==3){
                grid[y][x]=0;
                score+=50;
                power=true;
                c.restart();
            }
        }
        else{
            if(c.getElapsedTime().asSeconds()>5.0f){
                power=false;
                break;
            }
        }
    }
}
sem_t emptys,full,mut;

void pelletProducer(){
    bool firstNonWall=false;
    int x=rand()%(GRID_WIDTH-2)+1;
    int y=rand()%(GRID_HEIGHT-2)+1;
    for(int i=y;i<GRID_HEIGHT-1;i++){
        for(int j=x;j<GRID_WIDTH-1;j++){
            if(grid[i][j]==2){
                firstNonWall=true;
                grid[i][j]=3;
                break;
            }
        }
        if(firstNonWall)
            break;
    }

}

void* producer(void* arg) {
    while (1) {
        sem_wait(&emptys);  // Wait for space to produce a pellet
        sem_wait(&mut); // Enter critical section
        cout<<"Entered:"<<endl;

        pelletProducer();
        sem_post(&mut); // Leave critical section
        sem_post(&full);  // Signal that a pellet has been produced
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);
        sem_wait(&mut);
        pelletEater();
        sem_post(&mut);
        sem_post(&emptys);
    }
}

sf::IntRect closedUp(0,0,15,15);
sf::IntRect mediumUp(15,0,15,15);
sf::IntRect openUp(30,0,15,15);
sf::IntRect closedDown(45,0,15,15);
sf::IntRect mediumDown(60,0,15,15);
sf::IntRect openDown(75,0,15,15);
sf::IntRect closedLeft(90,0,15,15);
sf::IntRect mediumLeft(105,0,15,15);
sf::IntRect openLeft(120,0,15,15);
sf::IntRect closedRight(135,0,15,15);
sf::IntRect mediumRight(150,0,15,15);
sf::IntRect openRight(165,0,15,15);

void animatePacMan(Pacman &pacman, sf::Clock& animationClock) {
    // Check if it's time to toggle the animation frame
    if (animationClock.getElapsedTime().asMilliseconds() > 125) { 
        cout<<1;
        if(pacman.currentDirection==Vector2f(0,-1)){
            if (pacman.sprite.getTextureRect() == closedUp)
                pacman.sprite.setTextureRect(mediumUp);
            else if(pacman.sprite.getTextureRect() == mediumUp)
                pacman.sprite.setTextureRect(openUp);
            else
                pacman.sprite.setTextureRect(closedUp);
        }
        else if(pacman.currentDirection==Vector2f(0,1)){
            if (pacman.sprite.getTextureRect() == closedDown)
                pacman.sprite.setTextureRect(mediumDown);
            else if(pacman.sprite.getTextureRect() == mediumDown)
                pacman.sprite.setTextureRect(openDown);
            else
                pacman.sprite.setTextureRect(closedDown);
        }
        else if(pacman.currentDirection==Vector2f(-1,0)){
            if (pacman.sprite.getTextureRect() == closedLeft)
                pacman.sprite.setTextureRect(mediumLeft);
            else if(pacman.sprite.getTextureRect() == mediumLeft)
                pacman.sprite.setTextureRect(openLeft);
            else
                pacman.sprite.setTextureRect(closedLeft);
        }
        else{
            if (pacman.sprite.getTextureRect() == closedRight)
                pacman.sprite.setTextureRect(mediumRight);
            else if(pacman.sprite.getTextureRect() == mediumRight)
                pacman.sprite.setTextureRect(openRight);
            else
                pacman.sprite.setTextureRect(closedRight);
        }
        animationClock.restart();
    }
}

sem_t boost;
bool booster[4];
    IntRect boosted(120,15,15,15);
void *boostThread1(void* args){
    while(1){
        sem_wait(&boost);
        if(movingState[0]&&!booster[0])
            booster[0]=true;
        else if(movingState[1]&&!booster[1])
            booster[1]=true;
        else if(movingState[2]&&!booster[2])
            booster[2]=true;
        else if(movingState[3]&&!booster[3])
            booster[3]=true;
        sem_post(&boost);
    }
        if(booster[0]){
            ghosts[0].sprite.setTextureRect(boosted);
            cout<<"akfdjlajfkajfdk"<<endl;
        }
}

void *boostThread2(void* args){
    while(1){
        // cout<<"afhkahfdfakjfkahdfkasdhfkashkagd"<<endl;
        sem_wait(&boost);
        if(movingState[0]&&!booster[0])
            booster[0]=true;
        else if(movingState[1]&&!booster[1])
            booster[1]=true;
        else if(movingState[2]&&!booster[2])
            booster[2]=true;
        else if(movingState[3]&&!booster[3])
            booster[3]=true;
        sem_post(&boost);
    }
}

int main() {
    window.setFramerateLimit(100);
    Menu start;
    srand(time(0));
    start.display_menu(window);
    Clock clock,animationClock;
    Clock boostClock1,boostClock2,boostClock3,boostClock4;
    bool clockFlag1=false,clockFlag2=false,clockFlag3=false,clockFlag4=false;

    if (!b.loadFromFile("/home/kaf/Desktop/new/audio/eat_fruit.wav"))
        return -1;
    
    s.setBuffer(b);
    //GHOSTS
    gh1.top=15;gh1.left=30;gh1.width=15;gh1.height=15;
    gh2.top=30;gh2.left=30;gh2.width=15;gh2.height=15;
    gh3.top=45;gh3.left=30;gh3.width=15;gh3.height=15;
    gh4.top=60;gh4.left=30;gh4.width=15;gh4.height=15;
    g1.loadFromFile("/home/kaf/Desktop/new/things.png");
    g2.loadFromFile("/home/kaf/Desktop/new/things.png");
    g3.loadFromFile("/home/kaf/Desktop/new/things.png");
    g4.loadFromFile("/home/kaf/Desktop/new/things.png");
    ghosts[1].sprite.setTexture(g1);
    ghosts[2].sprite.setTexture(g2);
    ghosts[3].sprite.setTexture(g3);
    ghosts[0].sprite.setTexture(g4);
    ghosts[0].sprite.setTextureRect(gh1);
    ghosts[1].sprite.setTextureRect(gh2);
    ghosts[2].sprite.setTextureRect(gh3);
    ghosts[3].sprite.setTextureRect(gh4);
    Texture border;
    IntRect borderRect;borderRect.top=0;borderRect.left=0;borderRect.width=20;borderRect.height=20;
    border.loadFromFile("/home/kaf/Desktop/new/border1.png",borderRect);
    liveText.loadFromFile("/home/kaf/Desktop/new/lives.png");
    for(int i=0;i<3;i++){
        lives[i].setTexture(liveText);
        lives[i].setPosition(300+(i*50),500);
        lives[i].setScale(0.25f,0.25f);
    }

    font.loadFromFile("/home/kaf/Desktop/new/vaca.ttf");
    scores.setFont(font);
    scores.setFillColor(Color::White);
    scores.setStyle(Text::Bold|Text:: Underlined);
    scores.setPosition(0,500);

    for(int i=0;i<4;i++)
        movingState[i]=false;
    for(int i=0;i<4;i++)
        booster[i]=false;

    sem_init(&keys, 0, NUM_KEYS);
    sem_init(&permits, 0, NUM_PERMITS);
    sem_init(&reads, 0, NUM_GHOSTS);
    sem_init(&writes, 0, 1);             //value 1 since only one pacman
    sem_init(&emptys, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&mut,0,1);
    sem_init(&boost,0,2);

    pthread_t thread[NUM_GHOSTS],thread2,thread3,thread4,thread5,m1,m2,m3,m4,boost1,boost2;
    int ids[4]={1,2,3,4};
    for(int i=0;i<NUM_GHOSTS;i++)
        pthread_create(&thread[i],NULL,ghost,&ids[i]);
    pthread_create(&thread2,NULL,writers,NULL);
    pthread_create(&thread3,NULL,UserInterface,NULL);
    pthread_create(&thread4, NULL, producer, NULL);
    pthread_create(&thread5, NULL, consumer, NULL);
    pthread_create(&m1,NULL,movement1,NULL);
    pthread_create(&m2,NULL,movement2,NULL);
    pthread_create(&m3,NULL,movement3,NULL);
    pthread_create(&m4,NULL,movement4,NULL);
    pthread_create(&boost1,NULL,boostThread1,NULL);
    pthread_create(&boost2,NULL,boostThread2,NULL);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        pacman.setDirection(sf::Vector2f(0, -1));
                        break;
                    case sf::Keyboard::Down:
                        pacman.setDirection(sf::Vector2f(0, 1));
                        break;
                    case sf::Keyboard::Left:
                        pacman.setDirection(sf::Vector2f(-1, 0));
                        break;
                    case sf::Keyboard::Right:
                        pacman.setDirection(sf::Vector2f(1, 0));
                        break;
                    case sf::Keyboard::P:
                        start.display_menu(window);
                        break;
                    default:
                        break;
                }
            }
        }
        if(pelletsEaten==254)
            break;
        animatePacMan(pacman,animationClock);
        //cout<<"mut: "<<mut<<endl;
        float dt = clock.restart().asSeconds();
        window.clear();
        pacman.update(dt);
        pacman.transition();
        // Draw the grid
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                RectangleShape cell(Vector2f(CELL_SIZE -2, CELL_SIZE-2 ));
                if(grid[y][x]==1){
                    cell.setTexture(&border);
                    cell.setFillColor(Color::Blue);
                    cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                }
                else if(grid[y][x]==2){
                    cell.setScale(0.25f,0.25f);
                    cell.setFillColor(Color::Green);
                    cell.setPosition((x * CELL_SIZE)+7.5, (y * CELL_SIZE)+7.5);
                }
                else if(grid[y][x]==3){
                    cell.setScale(0.75f,0.75f);
                    cell.setFillColor(Color::Red);
                    cell.setPosition((x * CELL_SIZE)+2.5, (y * CELL_SIZE)+2.5);
                }
                if(!(y==10&&x==11))
                    window.draw(cell);
            }
        }

        if(booster[0]){
            ghosts[0].sprite.setTextureRect(boosted);
            
            cout<<boostClock1.getElapsedTime().asSeconds()<<"fakljfalkjdf"<<endl;
            if(!clockFlag1){
                boostClock1.restart();
                clockFlag1=true;
            }
            if(boostClock1.getElapsedTime().asSeconds()>5){
                booster[0]=false;
                ghosts[0].sprite.setTextureRect(gh1);
            }
        }
        if(booster[1]){
            ghosts[1].sprite.setTextureRect(boosted);
            
            cout<<boostClock2.getElapsedTime().asSeconds()<<"fakljfalkjdf"<<endl;
            if(!clockFlag2){
                boostClock2.restart();
                clockFlag2=true;
            }
            if(boostClock2.getElapsedTime().asSeconds()>5){
                booster[1]=false;
                ghosts[1].sprite.setTextureRect(gh2);
            }
        }
        if(booster[2]){
            ghosts[2].sprite.setTextureRect(boosted);
            
            cout<<boostClock3.getElapsedTime().asSeconds()<<"fakljfalkjdf"<<endl;
            if(!clockFlag3){
                boostClock3.restart();
                clockFlag3=true;
            }
            if(boostClock3.getElapsedTime().asSeconds()>5){
                booster[2]=false;
                ghosts[2].sprite.setTextureRect(gh3);
            }
        }
        if(booster[3]){
            ghosts[3].sprite.setTextureRect(boosted);
            
            cout<<boostClock4.getElapsedTime().asSeconds()<<"fakljfalkjdf"<<endl;
            if(!clockFlag4){
                boostClock4.restart();
                clockFlag4=true;
            }
            if(boostClock4.getElapsedTime().asSeconds()>5){
                booster[3]=false;
                ghosts[3].sprite.setTextureRect(gh4);
            }
        }

        cout<<pacman.sprite.getPosition().x<<' '<<pacman.sprite.getPosition().y<<endl;
        if(pelletsEaten==150)
            break;

        //cout<<"Permissions given:";
        for(int i=0;i<NUM_GHOSTS;i++)
            window.draw(ghosts[i].sprite);
        window.draw(pacman.sprite);
        for(int i=0;i<NUM_GHOSTS;i++){
        
            if(pacman.sprite.getGlobalBounds().intersects(ghosts[i].sprite.getGlobalBounds())){
                cout<<"a;afjadkfjafjalsdfkjfjdalkjflaksjdflajsdflasjlfdj"<<endl;
                pacman.position.x=150.04;
                pacman.position.y=190.04;
                liveCount--;
            }
        }
        window.draw(scores);
        for(int i=0;i<liveCount;i++)
            window.draw(lives[i]);
        window.display();
    }

    return 0;
}
