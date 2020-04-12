#include "gui_view.h"

#include <QGraphicsSimpleTextItem>

#include "GUI/ITEM/mybutton.h"



#include <QDebug>
#include <QRegExpValidator>
#include <QTextEdit>
#include <QTimer>


GUI_View::GUI_View(QWidget *parent) : QGraphicsView(parent)
{

    //window size and scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,900);

    //creating scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1024,900);
    setScene(scene);


    //display mainmenu
    this->displayMainMenu();

    connect(&this->game,SIGNAL(update()),this,SLOT(updateGui()));
    connect(&game,SIGNAL(hostStartedGame()),this,SLOT(displayGame()));


}

GUI_View::~GUI_View()
{

    delete scene;
}

void GUI_View::displayMainMenu()
{
    if(scene == nullptr)return;
    game.setMode(0);

    //clearing
    scene->clear();

    //bg patern and color
    this->setBackgroundBrush(QBrush(Qt::darkGray,Qt::SolidPattern));

    //title "PACMAN"
    QGraphicsTextItem *title = new QGraphicsTextItem(QString("PacMan"));
    QFont titleFont("comic sans",50,QFont::Bold);
    title->setFont(titleFont);
    int x = this->width()/2 - title->boundingRect().width()/2;
    int y = 100;
    title->setPos(x,y);
    scene->addItem(title);


    //singleplayer button
    MyButton *singleplayerButton = new MyButton(QString("Single Player"));
    x = this->width()/2 - singleplayerButton->boundingRect().width()/2;
    y = 275;
    singleplayerButton->setPos(x,y);
    connect(singleplayerButton,SIGNAL(clicked()),this,SLOT(singleplayerButtonClicked()));
    scene->addItem(singleplayerButton);

    //multiplayer button
    MyButton *multiplayerButton = new MyButton(QString("Multi Player"));
    x = this->width()/2 - multiplayerButton->boundingRect().width()/2;
    y = 350;
    multiplayerButton->setPos(x,y);
    connect(multiplayerButton,SIGNAL(clicked()),this,SLOT(multiplayerButtonClicked()));
    scene->addItem(multiplayerButton);

    //info button
    MyButton *creditsButton = new MyButton(QString("Credits"));
    x = this->width()/2 - creditsButton->boundingRect().width()/2;
    y = 425;
    creditsButton->setPos(x,y);
    //connect(singleplayerButton,SIGNAL(clicked()),this,SLOT(singleplayerButtonClicked()));//////do poprawy
    scene->addItem(creditsButton);

    //quit button
    MyButton *quitButton = new MyButton(QString("Quit"));
    x = this->width()/2 - quitButton->boundingRect().width()/2;
    y = 500;
    quitButton->setPos(x,y);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(quitButtonClicked()));
    scene->addItem(quitButton);

}

void GUI_View::displayGame()
{
    if(scene == nullptr)return;

    //clearing
    scene->clear();

    this->setBackgroundBrush(QBrush(Qt::white,Qt::SolidPattern));

    board = new Gui_Board(50,50,25,this->game);
    board->setFlag(QGraphicsItem::ItemIsFocusable);
    board->setFocus();

    //board->setFocus();
    connect(this,SIGNAL(updateCharacters(Game *)),board,SLOT(updateCharacters(Game *)));
    scene->addItem(board);

    //game start
    //game.start();

}

void GUI_View::singleplayerButtonClicked()
{
    game.setMode(1);
    displayGame();

    QTimer::singleShot(2000,&game,SLOT(start()));
    //game.start();

}

void GUI_View::multiplayerButtonClicked()
{
    scene->clear();

    //Host Button
    MyButton *hostGameButton = new MyButton(QString("Host Game"));
    int x = this->width()/2 - hostGameButton->boundingRect().width()/2;
    int y = 275;
    hostGameButton->setPos(x,y);
    connect(hostGameButton,SIGNAL(clicked()),this,SLOT(hostButtonClicked()));//////do poprawy
    scene->addItem(hostGameButton);

    //Join Button
    MyButton *joinGameButton = new MyButton(QString("Join Game"));
    x = this->width()/2 - joinGameButton->boundingRect().width()/2;
    y = 350;
    joinGameButton->setPos(x,y);
    connect(joinGameButton,SIGNAL(clicked()),this,SLOT(joinButtonClicked()));//////do poprawy
    scene->addItem(joinGameButton);

    //mainMenu Button
    MyButton *mainMenuButton = new MyButton(QString("Back"));
    x = this->width()/2 - mainMenuButton->boundingRect().width()/2;
    y = 700;
    mainMenuButton->setPos(x,y);
    connect(mainMenuButton,SIGNAL(clicked()),this,SLOT(mainMenuButtonClicked()));
    scene->addItem(mainMenuButton);

}

void GUI_View::quitButtonClicked()
{
    exit(0);
}

void GUI_View::mainMenuButtonClicked()
{
    this->displayMainMenu();
}

void GUI_View::hostButtonClicked()
{
    scene->clear();

    game.setMode(2);

    //startButton
    MyButton *startGameButton = new MyButton(QString("Start Game"));
    int x = this->width()/2 - startGameButton->boundingRect().width()/2;
    int y = 350;
    startGameButton->setPos(x,y);
    connect(startGameButton,SIGNAL(clicked()),this,SLOT(startGameButtonClicked()));//////do poprawy
    scene->addItem(startGameButton);

    //mainMenu Button
    MyButton *mainMenuButton = new MyButton(QString("Back"));
    x = this->width()/2 - mainMenuButton->boundingRect().width()/2;
    y = 700;
    mainMenuButton->setPos(x,y);
    connect(mainMenuButton,SIGNAL(clicked()),this,SLOT(mainMenuButtonClicked()));
    scene->addItem(mainMenuButton);

}

void GUI_View::joinButtonClicked()
{
    scene->clear();

    game.setMode(3);

    //lineedit box
    lineEditBox = new QLineEdit();
    int xsize=125,ysize=50;

    int x = this->width()/4 - xsize/2;
    int y = 300;
    lineEditBox->setGeometry(x,y,xsize,ysize);
    lineEditBox->setValidator( new QRegExpValidator(QRegExp("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}")) );
    lineEditBox->setPlaceholderText("192.168.100.100");
    lineEditBox->setFocus();
    scene->addWidget(lineEditBox);

    //connect button
    MyButton *connectButton = new MyButton(QString("Connect"));
    x = this->width()/4 - connectButton->boundingRect().width()/2;
    y = 400;
    connectButton->setPos(x,y);
    connect(connectButton,SIGNAL(clicked()),this,SLOT(connetButtonClicked()));
    scene->addItem(connectButton);

    //Player/Spectator button
    MyButton *playerSpectatorButton = new MyButton(QString("Player/Spectator"));
    x = (3*this->width()/4) - playerSpectatorButton->boundingRect().width()/2;
    y = 400;
    playerSpectatorButton->setPos(x,y);
    connect(playerSpectatorButton,SIGNAL(clicked()),this,SLOT(playerSpectatorButtonClicked()));
    scene->addItem(playerSpectatorButton);


    // back button
    MyButton *mainMenuButton = new MyButton(QString("Back"));
    x = this->width()/2 - mainMenuButton->boundingRect().width()/2;
    y = 700;
    mainMenuButton->setPos(x,y);
    connect(mainMenuButton,SIGNAL(clicked()),this,SLOT(mainMenuButtonClicked()));
    scene->addItem(mainMenuButton);


}

void GUI_View::connetButtonClicked()
{
    if(lineEditBox==nullptr)return;
    game.connectToHost(lineEditBox->text());
}

void GUI_View::playerSpectatorButtonClicked()
{
    if(game.getIsOnlineParticipant()){
        game.playerSpectatorRequest(false);
    }else{
        game.playerSpectatorRequest(true);
    }

}

void GUI_View::startGameButtonClicked()
{
    game.setIsLiveAlready();
    game.sendInitState();
    this->displayGame();
    QTimer::singleShot(2000,&game,SLOT(start()));
}

void GUI_View::updateGui()
{
    emit updateCharacters(&game);

}

