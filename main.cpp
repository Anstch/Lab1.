#include <iostream>
#include "filework.h"
#include <limits> // Для numeric_limits

int main() {
    VideoLibrary::VideoManager videoManager("videos.txt");
    setlocale(LC_ALL, "Russian");
    while (true) {
        std::cout << "Меню:\n"
            "  1   добавить видео\n"
            "  2   удалить видео\n"
            "  3   показать все видео\n"
            "  4   загрузить видео из файла\n"
            "  5   закончить работу\n\n";
        int choice;
        std::cin >> choice;
        //Очистка буфера
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            videoManager.addVideos();
            videoManager.saveVideos();
            break;
        case 2:
            videoManager.deleteVideos();
            videoManager.saveVideos();
            break;
        case 3:
            videoManager.displayVideos();
            videoManager.saveVideos();
            break;
        case 4: 
            videoManager.loadVideos();
            videoManager.displayVideos();
            break;
        
        case 5:
            return 0;
            break;
        default:
            std::cout << "Ошибка!\n\n";
            break;
        }
    }

    return 0;
}

