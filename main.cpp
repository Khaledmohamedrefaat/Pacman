#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <iostream>

#define N 21
#define M 26
using namespace std;
using namespace sf;
/** STRUCTS **/
struct Tile {
	int sizeX = 32;
	int sizeY = 32;
	int posX;
	int posY;
	Sprite sprite;
};
struct Dot {
	int sizeX = 32;
	int sizeY = 32;
	int posX;
	int posY;
	Sprite sprite;
};
struct Player {
	string directionToCheck = "none";
	string direction = "none";
	int posX;
	int posY;
	Sprite sprite;
};
struct point {
	int x, y, z;
};
point make_point(int x, int y, int z) {
	point t;
	t.x = x;
	t.y = y;
	t.z = z;
	return t;
}
struct QItem {
	int row;
	int col;
	int dist;
};
Player pacman;
/** VECTORS AND VARIABLES **/
/// Map : Vector --> 32 Row , 40 column
int checkMapVec[N][M];
int mapVec[32][40]{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1},
    {1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,1,1,0,0,1,1,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,1,1,0,0,1,1,1,1,0,0,1},
    {1,0,0,1,1,1,1,0,0,1,1,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,1,1,0,0,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1},
    {1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1},
    {1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1},
    {1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1},
    {1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

bool vis[N][M];
vector <Tile> tilemap;
vector <Dot> dotmap;
vector <Sprite> spriteGhost(4);
string dirst[4] = { "right" , "left" , "up" , "down" };
int dirx[4] = { 1,-1,0,0 };
int diry[4] = { 0,0,-1,1 };
bool ghostMoving[4], mrra = 0;
string ghostDir[4];
bool food = false, lose = false, win = false, paused = true;
int score = 0, speed = 4;
/** Functions **/
/** Store Tile And Dot Info **/
void getTheMap(sf::Texture &spriteSheet) {
	for (int rows = 0; rows < N; rows++)
	{
		for (int columns = 0; columns < M; columns++)
		{
			if (mapVec[rows][columns] == 1)
			{
				Tile block;
				block.posX = columns * 32;
				block.posY = rows * 32;
				block.sprite.setTexture(spriteSheet);
				block.sprite.setTextureRect(IntRect(264, 0, 32, 32));
				block.sprite.setPosition(block.posX, block.posY);
				tilemap.push_back(block);
			}
			else if (mapVec[rows][columns] == 0)
			{
				Dot block;
				block.posX = columns * 32;
				block.posY = rows * 32;
				block.sprite.setTexture(spriteSheet);
				block.sprite.setTextureRect(IntRect(298, 0, 32, 32));
				block.sprite.setPosition(block.posX, block.posY);
				dotmap.push_back(block);
			}
		}
	}
}
/** Check Collision with Tilemap **/
bool checkCollision(vector <Tile> tilemap, int posX, int posY, string type) {
	int x, y;
	if (type == "ghost") x = 32, y = 32;
	else x = 32, y = 32;
	for (int i = 0; i< tilemap.size(); i++)
	{
		if ((tilemap[i].sprite.getPosition().x < posX + x) && (tilemap[i].sprite.getPosition().x + y > posX) && (tilemap[i].sprite.getPosition().y < posY + x) && (tilemap[i].sprite.getPosition().y + y > posY))
		{
			return true;
		}

	}
	return false;
}
/** Check Collision of the ghosts **/
bool checkLose(vector<Sprite> spritevec, int posX, int posY) {
	for (int i = 0; i< spritevec.size(); i++)
	{
		if ((spritevec[i].getPosition().x < posX + 32) && (spritevec[i].getPosition().x + 32 > posX) && (spritevec[i].getPosition().y < posY + 32) && (spritevec[i].getPosition().y + 32 > posY))
		{
			return true;
		}

	}
	return false;
}
/** Destroy Eaten parts **/
void checkFood(int posX, int posY) {
	for (int i = 0; i< dotmap.size(); i++) {
		if ((dotmap[i].sprite.getPosition().x < posX + 32) && (dotmap[i].sprite.getPosition().x + 32 > posX) && (dotmap[i].sprite.getPosition().y < posY + 32) && (dotmap[i].sprite.getPosition().y + 32 > posY)) {
			dotmap.erase(dotmap.begin() + i);
			score++;
			food = true;
			i--;
		}
	}
}
/** Generate a Random direction **/
string generateDir() {
	int rnd = rand() % 4;
	if (rnd == 0)return "right";
	if (rnd == 1)return "left";
	if (rnd == 2)return "up";
	if (rnd == 3)return "down";
}
void pacmanMove(int pix) {
	if (pacman.direction == "right")pacman.posX += pix;
	else if (pacman.direction == "left")pacman.posX -= pix;
	else if (pacman.direction == "up")pacman.posY -= pix;
	else if (pacman.direction == "down")pacman.posY += pix;
	pacman.sprite.setPosition(pacman.posX, pacman.posY);
}
void pacmanTextRec() {
	if (pacman.direction == "right")pacman.sprite.setTextureRect(IntRect(0, 0, 64, 64));
	else if (pacman.direction == "left")pacman.sprite.setTextureRect(IntRect(66, 0, 64, 64));
	else if (pacman.direction == "up")pacman.sprite.setTextureRect(IntRect(132, 0, 64, 64));
	else if (pacman.direction == "down")pacman.sprite.setTextureRect(IntRect(198, 0, 64, 64));
}
void PacmansMovement(int speed) {
	pacmanMove(speed);
	if (pacman.directionToCheck != "none") {
		string dire = pacman.direction;
		pacman.direction = pacman.directionToCheck;
		pacmanMove(speed);
		if (checkCollision(tilemap, pacman.posX, pacman.posY, "pacman")) {
			pacmanMove(-speed);
			pacman.direction = dire;
			if (checkCollision(tilemap, pacman.posX, pacman.posY, "pacman")) {
				pacmanMove(-speed);
				pacman.direction = "none";
				pacman.directionToCheck = "none";
			}
		}
		else {
			pacman.directionToCheck = "none";
			pacmanMove(-speed);
		}
	}
	else if (checkCollision(tilemap, pacman.posX, pacman.posY, "pacman")) {
		pacmanMove(-speed);
		pacman.direction = "none";
	}
	pacmanTextRec();
}
void setDir(string dir) {
	if (pacman.direction == "none")pacman.direction = dir;
	else pacman.directionToCheck = dir;
}
string last = "right";
bool isCellValid(int mapVec[N][M], int x, int y) {
	if (mapVec[x + 1][y] == 1 || mapVec[x][y + 1] == 1 || mapVec[x + 1][y + 1] == 1)return false;
	return true;
}
int mshbfs(int mapVec[N][M]) {
	point source = make_point(0, 0, 0);
	bool visited[N][M];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (mapVec[i][j] == 1 || !isCellValid(mapVec, i, j))visited[i][j] = true;
			else visited[i][j] = false;
			if (mapVec[i][j] == 3)source.x = i, source.y = j;

		}
	}
	queue<point> q;
	q.push(source);
	visited[source.x][source.y] = true;
	while (!q.empty()) {
		point p = make_point(q.front().x, q.front().y, q.front().z);
		q.pop();
		if (mapVec[p.x][p.y] == 5)return p.z;
		if (p.x - 1 >= 0 && visited[p.x - 1][p.y] == false) {
			q.push(make_point(p.x - 1, p.y, p.z + 1));
			visited[p.x - 1][p.y] = true;
			if (mapVec[p.x - 1][p.y] == 5)last = "down";
		}
		if (p.x + 1 < N && visited[p.x + 1][p.y] == false) {
			q.push(make_point(p.x + 1, p.y, p.z + 1));
			visited[p.x + 1][p.y] = true;
			if (mapVec[p.x + 1][p.y] == 5)last = "up";
		}
		if (p.y - 1 >= 0 && visited[p.x][p.y - 1] == false) {
			q.push(make_point(p.x, p.y - 1, p.z + 1));
			visited[p.x][p.y - 1] = true;
			if (mapVec[p.x][p.y - 1] == 5)last = "right";
		}
		if (p.y + 1 < M &&visited[p.x][p.y + 1] == false) {
			q.push(make_point(p.x, p.y + 1, p.z + 1));
			visited[p.x][p.y + 1] = true;
			if (mapVec[p.x][p.y + 1] == 5)last = "left";
		}
	}
	return -1;
}
string OppDirection(string dir) {
	if (dir == "right")return "left";
	if (dir == "left")return "right";
	if (dir == "down")return "up";
	if (dir == "up")return "down";
}
int main()
{
	/** FONT **/
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	Text scoreText, messageText, loseText, winText;
	/** Score Text **/
	scoreText.setFont(font);
	scoreText.setString("Score = 0");
	scoreText.setCharacterSize(35);
	scoreText.setFillColor(Color::Red);
	scoreText.setPosition(0, 0);
	/** Message Text **/
	messageText.setFont(font);
	messageText.setString("Press Enter to start!");
	messageText.setCharacterSize(50);
	messageText.setFillColor(Color::White);
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition((M * 32) / 2.0f, (N * 32) / 2.0f);
	/** Lose Text **/
	loseText.setFont(font);
	loseText.setString("You Lose and your Score is : 000");
	loseText.setCharacterSize(30);
	loseText.setFillColor(Color::Red);
	FloatRect loseRect = loseText.getLocalBounds();
	loseText.setOrigin(loseRect.left + loseRect.width / 2.0f, loseRect.top + loseRect.height / 2.0f);
	loseText.setPosition((M * 32) / 2.0f, (N * 32) / 2.0f);
	/** Win Text **/
	winText.setFont(font);
	winText.setString("You Won and your Score is : 000");
	winText.setCharacterSize(30);
	winText.setFillColor(Color::Red);
	FloatRect winRect = winText.getLocalBounds();
	winText.setOrigin(winRect.left + winRect.width / 2.0f, winRect.top + winRect.height / 2.0f);
	winText.setPosition((M * 32) / 2.0f, (N * 32) / 2.0f);
	/** Ghosts **/
	Texture textureGhost1, textureGhost2, textureGhost3, textureGhost4;
	textureGhost1.loadFromFile("graphics/ghost1.png");
	spriteGhost[0].setTexture(textureGhost1);
	spriteGhost[0].setPosition(9 * 32, 1 * 32);
	textureGhost2.loadFromFile("graphics/ghost2.png");
	spriteGhost[1].setTexture(textureGhost2);
	spriteGhost[1].setPosition(11 * 32, 1 * 32);
	textureGhost3.loadFromFile("graphics/ghost3.png");
	spriteGhost[2].setTexture(textureGhost3);
	spriteGhost[2].setPosition(13 * 32, 1 * 32);
	textureGhost4.loadFromFile("graphics/ghost4.png");
	spriteGhost[3].setTexture(textureGhost4);
	spriteGhost[3].setPosition(15 * 32, 1 * 32);
	/** SPRITESHEET **/
	Texture spriteSheet;
	spriteSheet.loadFromFile("graphics/spriteSheetSmall.png");
	Sprite Check;
	Check.setTexture(spriteSheet);
	Check.setTextureRect(IntRect(264, 0, 32, 32));
	Check.setPosition(4 * 32, 4 * 32);
	/** Drawing The Window **/
	RenderWindow appWindow(VideoMode(M * 32, N * 32), "Pacman");
	appWindow.setFramerateLimit(60);
	appWindow.setVerticalSyncEnabled(true);
	/** OBJECTS **/
	pacman.posX = 32;
	pacman.posY = 32;
	pacman.sprite.setTexture(spriteSheet);
	pacman.sprite.setTextureRect(IntRect(0, 0, 64, 64));
	pacman.sprite.setPosition(pacman.posX, pacman.posY);
	/** Sound **/
	SoundBuffer BeginBuffer;
	BeginBuffer.loadFromFile("sound/pacman_beginning.wav");
	Sound BeginSound;
	BeginSound.setBuffer(BeginBuffer);
	BeginSound.play();
	SoundBuffer EatBuffer;
	EatBuffer.loadFromFile("sound/pacman_chomp.wav");
	Sound EatSound;
	EatSound.setBuffer(EatBuffer);
	SoundBuffer DieBuffer;
	DieBuffer.loadFromFile("sound/pacman_death.wav");
	Sound DieSound;
	DieSound.setBuffer(DieBuffer);
	/** Main Game Loop **/
	getTheMap(spriteSheet); //Drawing the map with the 2D Vector
	while (appWindow.isOpen()) {
		/** Updating The Scene **/
		Event event;
		while (appWindow.pollEvent(event)) {
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))appWindow.close();
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)paused = false;
			if (!paused) {
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right)setDir("right");
				else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)setDir("left");
				else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)setDir("up");
				else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)setDir("down");
			}
		}
		if (!paused) {
			/** Moving Pacman **/
			pacman.posX = pacman.sprite.getPosition().x;
			pacman.posY = pacman.sprite.getPosition().y;
			PacmansMovement(4);

			/** Move the 4 Ghosts **/
			for (int j = 0; j < 4;j++) {
				int ghostX = spriteGhost[j].getPosition().x / 32;
				int ghostY = spriteGhost[j].getPosition().y / 32;
				int PacX = pacman.posX / 32;
				int PacY = pacman.posY / 32;

				checkMapVec[PacY][PacX] = 3;
				checkMapVec[ghostY][ghostX] = 5;
				cout << PacX << " " << PacY << " " << ghostX << " " << ghostY << endl;
				cout << mshbfs(checkMapVec) << endl;
				cout << last << endl;
				ghostDir[j] = last, ghostMoving[j] = true;
				for (int i = 0;i < 4;i++) {
					if (ghostDir[j] == dirst[i]) {
						//if (!checkCollision(tilemap, spriteGhost[j].getPosition().x + dirx[i], spriteGhost[j].getPosition().y + diry[i], "ghost")) {
							spriteGhost[j].move(dirx[i], diry[i]);
							break;
						//}
						//else { ghostMoving[j] = false; }
					}
				}
				/*
				if(!ghostMoving[j])ghostDir[j]=generateDir(),ghostMoving[j]=true;
				for (int i = 0;i < 4;i++){
				if (ghostDir[j] == dirst[i]){
				if (!checkCollision(tilemap, spriteGhost[j].getPosition().x + dirx[i], spriteGhost[j].getPosition().y + diry[i] , "ghost")){
				spriteGhost[j].move(dirx[i], diry[i]);
				break;
				}
				else { ghostMoving[j] = false; }
				}
				}
				*/
			}
			/*for ( int i = 0 ; i < 1 ; i++ ){
			int ghostX = spriteGhost[i].getPosition().x/32 ;
			int ghostY = spriteGhost[i].getPosition().y/32;
			int PacX = pacman.posX/32;
			int PacY = pacman.posY/32;
			//cout<<ghostX << " " << ghostY << " " << PacX << " " << PacY << endl;
			int temp = step(ghostX,ghostY,PacX,PacY);
			//cout << i << " " << temp << endl;
			if(!mrra)cout<<"aa",mrra=true,spriteGhost[0].setPosition(dirx[temp],diry[temp]);
			}*/

			/** Food **/
			food = false;
			checkFood(pacman.sprite.getPosition().x, pacman.sprite.getPosition().y);
			if (food)EatSound.play();

			/** Update The String Streams **/
			stringstream Streams[3]; // Score , Lose , Win
			Streams[0] << "Score = " << score;
			scoreText.setString(Streams[0].str());
			Streams[1] << "You Lose and your Score is : " << score;
			loseText.setString(Streams[1].str());
			Streams[2] << "You Won and your Score is : " << score;
			winText.setString(Streams[2].str());

			/** Check Lose & Win **/
			if (checkLose(spriteGhost, pacman.sprite.getPosition().x, pacman.sprite.getPosition().y))paused = true, lose = true, DieSound.play();
			if (dotmap.size() == 0) win = true, paused = true;
		}
		/** Drawing The Scene **/
		appWindow.clear(Color::Black);
		for (int i = 0; i<tilemap.size(); i++)appWindow.draw(tilemap[i].sprite);
		for (int i = 0; i<dotmap.size(); i++)appWindow.draw(dotmap[i].sprite);
		appWindow.draw(pacman.sprite);
		for (int i = 0; i < 4; i++)appWindow.draw(spriteGhost[i]);
		appWindow.draw(scoreText);
		if (paused) {
			if (lose) appWindow.draw(loseText);
			else if (win) appWindow.draw(winText);
			else appWindow.draw(messageText);
		}
		appWindow.display();
		/** Delay **/
		sleep(microseconds(50));
	}
	return 0;
}
