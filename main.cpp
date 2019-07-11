//Cuong Phan
//04/05/18
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>
using namespace sf;
class Bullet
{
public:
    Sprite shape;
    Bullet(Texture*texture, Vector2f pos) //constructor a class Bullet
    {
        this->shape.setTexture(*texture);
        this->shape.setScale (0.07f, 0.07f);
        this->shape.setPosition(pos); // create bullet at player's position
        
    }
    ~Bullet(){} //Destructor of the class Bullet
    
};

class Player
{
public:
    Sprite shape;
    Texture*texture;
    int HP;
    int HPMax;
    std:: vector<Bullet> bullets;
    Player (Texture*texture ) //constructor of class Player
    {
        this ->HPMax = 10;
        this->HP =this ->HPMax;
        this -> texture= texture;
        this ->shape.setTexture(*texture);
        this->shape.setScale(0.1f,0.1f);
    }
    ~ Player(){} //Destructor of class Player
    
    
};
class DefendObject
{
public:
    Sprite shape;
    Texture*texture;
    DefendObject(Texture*texture) //Constructor of class Defend Object
    {
        this->texture=texture;
        this->shape.setTexture(*texture);
    }
};
class LetterA
{
     public:
    Sprite shape;
    char HP;
    char HPMax;
    LetterA(Texture*texture, Vector2u windowSize) //Constructor of class LetterA, which generate enemy
    {
        this->HPMax= rand()%26+65;
        this->HP= this->HPMax;
        this ->shape.setTexture(*texture);
        this->shape.setScale(0.1f, 0.1f);
        this->shape.setPosition(windowSize.x- this->shape.getGlobalBounds().width, rand()%(int)windowSize.y- this->shape.getGlobalBounds().height);  //genrate enemy randomly on the screen, with random y position
    }
    ~LetterA(){}
    
};



int main ()
{
	bool PressEnter = false;
    srand(time(NULL));
   // RenderWindow window(VideoMode::getFullscreenModes().front(),"Typing Game!", Style::Fullscreen);
    RenderWindow window(VideoMode(1920,1080), "Typing Game!");
    window.setFramerateLimit(60); //set the frame speed of the game
    bool WantPlayAgain = false; //declare a boolean variable to control the game loop
    //Below is the loading image, audio, character font files into the program:
    Sprite background ;
    Texture backgroundTex;
    Music music;
    music.openFromFile("background.wav");
    music.setLoop(true);
    music.play();
    SoundBuffer shotting, explosion;
    shotting.loadFromFile("shooting sound.wav");
    explosion.loadFromFile("Explosion.wav");
    Sound sound, soundexplosion;
    sound.setBuffer(shotting);
    soundexplosion.setBuffer(explosion);
    
    backgroundTex.loadFromFile("space_earth_planets_96790_3200x2400.jpg");
    backgroundTex.setRepeated(true);
    background.setTexture(backgroundTex);
    Texture playerTex;
    playerTex.loadFromFile("Ship.png");
    Texture LetterATex, LetterBTex, LetterCTex, LetterDTex,LetterRTex, LetterOTex;
    LetterATex.loadFromFile("Enemies.png");
    Texture bulletTex;
	Texture t, t1, t2, t3;
	
   t1.loadFromFile("type_A.png");
    t2.loadFromFile("starship.png");
	t3.loadFromFile("splashscreen.png");
	Sprite SplashScreen;
	SplashScreen.setTexture(t3);
      bulletTex.loadFromFile("Missilei.png");
	  Sprite boomExplosion;
	  boomExplosion.setTexture(t1);
	  boomExplosion.setScale(0.3f, 0.3f);
   
   //UI init
    Font font;
    font.loadFromFile("sansation.ttf");
    //ending the loading file process
    int Score=0; //Assign the value of Score = 0 when the game start
    //Below is the setup of all Text appear all on the screen. Set Text font, character size, color.. for gameover text, score text, play again text, text display player's health, text ships carry...
    Text score, round;
    score.setFont(font);
    score.setFillColor(Color::White);
    score.setOutlineThickness(2);
    score.setOutlineColor(Color::Red);
    score.setPosition(10.f, 10.f);
    score.setCharacterSize(30);
    round.setFont(font);
    round.setFillColor(Color::White);
    round.setOutlineThickness(2);
    round.setOutlineColor(Color::Red);
	Text hpText, InstructionText, IntroText;
    hpText.setFont(font);
    hpText.setCharacterSize(30);
    hpText.setFillColor(Color::White);
    hpText.setOutlineThickness(2);
    hpText.setOutlineColor(Color::Red);
	InstructionText.setFont(font);
	InstructionText.setCharacterSize(30);
	InstructionText.setFillColor(Color::White);
	InstructionText.setOutlineThickness(2);
	InstructionText.setOutlineColor(Color::Blue);
	IntroText.setFont(font);
	IntroText.setCharacterSize(50);
	IntroText.setFillColor(Color::White);
	IntroText.setOutlineColor(Color::Red);
	IntroText.setOutlineThickness(2);
	InstructionText.setString("		GROUP 1 \n \n CUONG  M  PHAN \n \n CHUONG  PHAN \n \n CUONG  N  PHAN \n \n RICHARD  CASTILLO \n \n ETHAN  KHWAJA");
	IntroText.setString("PLEASE PRESS ENTER TO PLAY THE GAME");
    Text eHpText;
    eHpText.setFont(font);
    eHpText.setCharacterSize(35);
    eHpText.setFillColor(Color::Blue);
    eHpText.setOutlineThickness(3);
    eHpText.setOutlineColor(Color::White);
    Text gameOverText, PlayAgainText;
    gameOverText.setFont(font);
    gameOverText.setFillColor(Color::White);
    gameOverText.setOutlineThickness(2);
    gameOverText.setOutlineColor(Color::Red);
    gameOverText.setPosition(window.getSize().x/2-100, window.getSize().y/2 - 300);
    gameOverText.setCharacterSize(50);
    gameOverText.setString("GAME OVER");
    PlayAgainText.setFont(font);
    PlayAgainText.setFillColor(Color::White);
    PlayAgainText.setOutlineThickness(2);
    PlayAgainText.setOutlineColor(Color::Blue);
    PlayAgainText.setCharacterSize(50);
    PlayAgainText.setPosition(window.getSize().x/2-300, window.getSize().y/2-200);
    PlayAgainText.setString(" DO YOU WANT TO PLAY AGAIN ? \n PRESS Y FOR YES OR N FOR NO");
    //Ending of the Game Text setup
    Player player (&playerTex); //loading the image of the spaceship / player image
    DefendObject object (&t2); //declare an object same type as class DefendObject and load information of Texture t2 to it.
    int shootTimer=20; //control the shooting time of the player by setting its value is 20.
    int enemySpawnTimer=0; //initilizing the speed at which enemies appear on the screen
    int Round=1; //intinizing a varible to count round.
    std::vector<LetterA> LetterAs; //initializing a vector LetterAs to contain all elements generated in class LetterA above.
	LetterAs.push_back(LetterA(&LetterATex, window.getSize())); //getting the Texture and the size of the windows back to vector Letter As
    
	while (window.isOpen()) // the beginng of the while loop when the SFML window is running
	{
		Event event;
		while (window.pollEvent(event)) //beginning

		{
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed&&event.key.code == sf::Keyboard::Escape) window.close();
		}
		//Background issues
		SplashScreen.setScale(0.7, 0.7);
		window.draw(SplashScreen);
		InstructionText.setPosition(800, 700);
		IntroText.setPosition(400, 500);
		window.draw(InstructionText);
		window.draw(IntroText);
		//	InstructionText.move(1, 1);
		if (Keyboard::isKeyPressed(Keyboard::Return)) PressEnter = true;
		if (PressEnter)
		{
			background.setOrigin(0, 0);
			background.move(-0.5, -0.5);
			window.draw(background);
			if (background.getPosition().y <= -500) background.setPosition(0, 0);
		}

		// clock.restart();
			do
			{
				bool PlayAgain = false;
				WantPlayAgain = PlayAgain;
				if (player.HP > 0)
				{
					//Player
					hpText.setPosition(300.0f, 10.0f);
					hpText.setString("HP: " + std::to_string(player.HP) + "/" + std::to_string(player.HPMax));
					round.setPosition(700, 10);
					round.setString("ROUND: " + std::to_string(Round));
					//Collison with window
					if (player.shape.getPosition().x <= 0) // Left
						player.shape.setPosition(0.f, player.shape.getPosition().y);
					if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width)
						player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y); // Right
					if (player.shape.getPosition().y <= 0) // Top
						player.shape.setPosition(player.shape.getPosition().x, 0.f);
					if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //Bottom
						player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);
					//Update controls
					if (shootTimer < 15) shootTimer++;

					//bullets
					for (size_t i = 0; i < player.bullets.size(); i++)
					{
						//Move
						player.bullets[i].shape.move(20.0f, 0.f);
						//Out of window bounds
						if (player.bullets[i].shape.getPosition().x > window.getSize().x)
						{
							player.bullets.erase(player.bullets.begin() + i);
							break;
						}
						//enemy collision
						for (size_t k = 0; k < LetterAs.size(); k++)
						{
							if (player.bullets[i].shape.getGlobalBounds().intersects(LetterAs[k].shape.getGlobalBounds()))
							{
								// if (LetterAs[k].HP<=1)
								{

									boomExplosion.setPosition(LetterAs[k].shape.getPosition().x, LetterAs[k].shape.getPosition().y);
									window.draw(boomExplosion);
									Score++;

									soundexplosion.play();
									LetterAs.erase(LetterAs.begin() + k);
								}
								// else LetterAs[k].HP--; //Enemytakedamge
								player.bullets.erase(player.bullets.begin() + i);

								break;
							}
						}
					}

					//Update enemy
					int numbEnemy = 70;
					if (Score < 10) numbEnemy = 70;
					if (Score > 10 && Score < 20) { numbEnemy = 50; Round = 2; }
					if (Score > 20) { numbEnemy = 25; Round = 3; }
					if (enemySpawnTimer < numbEnemy)
						enemySpawnTimer++;
					if (enemySpawnTimer >= numbEnemy)
					{
						LetterAs.push_back(LetterA(&LetterATex, window.getSize()));
						enemySpawnTimer = 0; //reset timer

					}
					for (size_t i = 0; i < LetterAs.size(); i++)
					{
						if (LetterAs[i].shape.getPosition().y <= 50) // Top
							LetterAs[i].shape.setPosition(LetterAs[i].shape.getPosition().x, LetterAs[i].shape.getPosition().y + 100.f);
						LetterAs[i].shape.move(-6.f, 0.f);
						if (LetterAs[i].shape.getPosition().x <= 0 - LetterAs[i].shape.getGlobalBounds().width)
						{
							LetterAs.erase(LetterAs.begin() + i);
							break;
						}
						if (PressEnter)
						if (LetterAs[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
						{
							LetterAs.erase(LetterAs.begin() + i);
							soundexplosion.play();
							boomExplosion.setPosition(LetterAs[i].shape.getPosition().x, LetterAs[i].shape.getPosition().y);
							window.draw(boomExplosion);
							player.HP--;
							//Player take damage;
							break;
						}
						//Intersect Object Round 1
						if (PressEnter)
						if (Round >= 1 && LetterAs[i].shape.getGlobalBounds().intersects(object.shape.getGlobalBounds()))
							// ()
						{
							boomExplosion.setPosition(LetterAs[i].shape.getPosition().x, LetterAs[i].shape.getPosition().y);
							window.draw(boomExplosion);
							LetterAs.erase(LetterAs.begin() + i);
							soundexplosion.play();
							player.HP--;
							break;

						}

					}




					//UI update
					score.setString("Score: " + std::to_string(Score));
				}

				//Draw........Objects
				if (Round >= 1)
				{
					object.shape.setOrigin(0, 0);
					object.shape.setScale(0.5f, 0.5f);
					object.shape.move(0, 0.5);
					if (object.shape.getPosition().y >= window.getSize().y - object.shape.getGlobalBounds().height) object.shape.setPosition(0, 0);
					if (PressEnter)	window.draw(object.shape);
				}


				//Player

				if (PressEnter)	window.draw(player.shape);
				//Update
				//Draw Bullet

				for (size_t i = 0; i < player.bullets.size(); i++)
				{
					window.draw(player.bullets[i].shape);
				}
				//Enemy
				for (size_t i = 0; i < LetterAs.size(); i++)
				{
					eHpText.setString(LetterAs[i].HPMax);
					eHpText.setPosition(LetterAs[i].shape.getPosition().x, LetterAs[i].shape.getPosition().y - eHpText.getGlobalBounds().height - 10);
					// player.shape.setPosition(0.f,LetterAs[i].shape.getPosition().y);
					if (Keyboard::isKeyPressed(Keyboard::A) && LetterAs[i].HPMax == 65 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::B) && LetterAs[i].HPMax == 66 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::C) && LetterAs[i].HPMax == 67 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::D) && LetterAs[i].HPMax == 68 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::E) && LetterAs[i].HPMax == 69 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::F) && LetterAs[i].HPMax == 70 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::G) && LetterAs[i].HPMax == 71 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::H) && LetterAs[i].HPMax == 72 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::I) && LetterAs[i].HPMax == 73 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::J) && LetterAs[i].HPMax == 74 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::K) && LetterAs[i].HPMax == 75 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::L) && LetterAs[i].HPMax == 76 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::M) && LetterAs[i].HPMax == 77 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::N) && LetterAs[i].HPMax == 78 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::O) && LetterAs[i].HPMax == 79 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::P) && LetterAs[i].HPMax == 80 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::Q) && LetterAs[i].HPMax == 81 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::R) && LetterAs[i].HPMax == 82 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::S) && LetterAs[i].HPMax == 83 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::T) && LetterAs[i].HPMax == 84 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::U) && LetterAs[i].HPMax == 85 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::V) && LetterAs[i].HPMax == 86 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::W) && LetterAs[i].HPMax == 87 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0;
						sound.play();
						//reset timer
					}
					if (Keyboard::isKeyPressed(Keyboard::X) && LetterAs[i].HPMax == 88 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::Y) && LetterAs[i].HPMax == 89 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (Keyboard::isKeyPressed(Keyboard::Z) && LetterAs[i].HPMax == 90 && shootTimer >= 15)
					{
						player.shape.setPosition(200, LetterAs[i].shape.getPosition().y);
						player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
						shootTimer = 0; //reset timer
						sound.play();
					}
					if (PressEnter) window.draw(eHpText);
					if (PressEnter) window.draw(LetterAs[i].shape);

				}
				//UI
				if (PressEnter)
				{
					window.draw(score);
					window.draw(hpText);
					window.draw(round);
				}
				if (player.HP <= 0)
				{
					window.draw(gameOverText);
					window.draw(PlayAgainText);
					if (Keyboard::isKeyPressed(Keyboard::Y))
					{
						PlayAgain = true;
						Score = 0;
						player.HP = 10;
						Round = 1;
						window.clear();
					}
					else if (Keyboard::isKeyPressed(Keyboard::N))
						return EXIT_SUCCESS;
				}
				//
				window.display();

			} while (WantPlayAgain == true);
		}

	
 

    return EXIT_SUCCESS;
}
