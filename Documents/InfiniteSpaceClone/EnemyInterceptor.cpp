#include "EnemyInterceptor.h"

std::vector<EnemyInterceptor*>  EnemyInterceptor::interceptors;
bool EnemyInterceptor::shipHit = false;

EnemyInterceptor::EnemyInterceptor() {

   // Coordinate temp;
   /* for(int i=0; i<20; i++) {
        temp.x = i*50; temp.y = i*50;
        path.push_back(temp);
    }*/
    speed = 20;
    hitTimer = 0;
    pathI = 0;

    //char buffer [1];
    //std::string temp = "path1.txt";
    //std::string temp2(itoa(rand()%5 + 1, buffer, 10));
    //temp.replace(4,1,temp2);

    FILE* pathFile = fopen("path1.txt", "r");

    int tempX, tempY;
    Coordinate tempPath;

    while(!feof(pathFile)) {

        fscanf(pathFile, "%d:%d", &tempX, &tempY);
        tempPath.x = tempX; tempPath.y = tempY;
        path.push_back(tempPath);

    }

    fclose(pathFile);

    position = path.at(0);

}

Coordinate EnemyInterceptor::getPosition(int ship) {

 /*   if(EnemyInterceptor::interceptors.at(ship)->position.x == EnemyInterceptor::interceptors.at(ship)->path.at(EnemyInterceptor::i + 1).x &&
        EnemyInterceptor::interceptors.at(ship)->position.y == EnemyInterceptor::interceptors.at(ship)->path.at(EnemyInterceptor::i + 1).y) {
        if(i < EnemyInterceptor::interceptors.size())
            i++;
    }*/
    Coordinate curPos = EnemyInterceptor::interceptors.at(ship)->position;
    int tempI = EnemyInterceptor::interceptors.at(ship)->pathI;

    if(tempI < EnemyInterceptor::interceptors.at(ship)->path.size() - 1) {


        Coordinate pathPos = EnemyInterceptor::interceptors.at(ship)->path.at(tempI + 1);

        if(curPos.x - pathPos.x < 0) {
            curPos.x += EnemyInterceptor::interceptors.at(ship)->speed/10;
            if(curPos.x - pathPos.x >= 0 && curPos.y - pathPos.y >= 0)
               tempI++;
        }
        else {
            curPos.x -= EnemyInterceptor::interceptors.at(ship)->speed/10;
            if(curPos.x - pathPos.x <= 0 && curPos.y - pathPos.y <= 0)
               tempI++;
        }

        if(curPos.y - pathPos.y < 0) {
            curPos.y += EnemyInterceptor::interceptors.at(ship)->speed/10;
            if(curPos.x - pathPos.x >= 0 && curPos.y - pathPos.y >= 0)
               tempI++;
        }
        else {
            curPos.y -= EnemyInterceptor::interceptors.at(ship)->speed/10;
            if(curPos.x - pathPos.x <= 0 && curPos.y - pathPos.y <= 0)
               tempI++;
        }





    }

    EnemyInterceptor::interceptors.at(ship)->pathI = tempI;
    EnemyInterceptor::interceptors.at(ship)->position = curPos;
    Coordinate temp = EnemyInterceptor::interceptors.at(ship)->position;
    return temp;

}

bool EnemyInterceptor::exitBattle() {

    int i=0;
    while(i<EnemyInterceptor::interceptors.size()) {
        EnemyInterceptor::interceptors.at(i)->position = EnemyInterceptor::interceptors.at(i)->path.at(0);
        EnemyInterceptor::interceptors.at(i)->pathI = 0;

        i++;
    }

    return true;

}
