#include "filework.h"
#include <iostream>
#include <fstream> //работа с файлами
#include <iomanip> //для setw
using namespace std;
//using namespace VideoLibrary;

std::ostream& operator<<(std::ostream& os, const Video& video) {
        os << video.title << '\n';
        os << video.author << '\n';
        os << video.likes << '\n';
        return os;
}

std::istream& operator>>(std::istream& is, Video& video) {
        is.getline(video.title, 100);
        is.getline(video.author, 100);
        is >> video.likes;
        is.ignore();
        return is;
}


namespace VideoLibrary {

    VideoManager::VideoManager(const char* filename) : pRoot(nullptr), VideoFile(filename) {} //берем из класса в заголовочком файле

    

    VideoManager::~VideoManager() { //деструктив 
        removeAll();
    }

    Video* VideoManager::createVideo() {
        return new Video;
    }

    void VideoManager::destroyVideo(Video* video) {
        delete video;
    }

    void VideoManager::loadVideos() {
        std::ifstream file(VideoFile, std::ios::binary); // Используем бинарный режим
        if (!file.is_open()) {
            std::cout << "Файл не найден\n";
            return;
        }

        removeAll(); // Удаляем всё, что хранится в памяти в этот момент, чтобы записать по новой всё из файла

        Video tempVideo; // Объект для временного хранения прочитанного видео
        while (file.read(reinterpret_cast<char*>(&tempVideo), sizeof(Video))) { //читаем файл
            if (file.gcount() == sizeof(Video)) {
                // Выделяем новую память для видео.
                Video* newVideo = new Video(tempVideo); //сохраняет адрес нового объекта в указателе newVideo
                newVideo->pPrev = pRoot; 
                pRoot = newVideo;
            }
            else {
                // Проверка на конец файла и/или ошибки чтения.
                if (!file.eof()) {
                    std::cerr << "Ошибка чтения из файла.\n"; 
                }
                break;
            }
        }

        file.close();
        std::cout << "Видео загружены.\n";
    }


    void VideoManager::saveVideos() {
        std::ofstream file(VideoFile, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "Файл не найден\n";
            return;
        }

        // Проходим по связному списку и записываем видео в файл.
        Video* current = pRoot;
        while (current != nullptr) {
            file.write(reinterpret_cast<const char*>(current), sizeof(Video));
            current = current->pPrev;
        }

        file.close();
    }

    void VideoManager::deleteVideos() {
        int index;
        std::cout << "Введите номер элемента, который желаете удалить: \n";
        std::cin >> index;
        index--;

        if (pRoot == nullptr) {
            std::cout << "Список видео пуст\n";
            return;
        }

        if (index < 0) {
            std::cout << "Ошибка! Введен некорректный номер!\n";
            return;
        }

        Video* pRem = pRoot;
        if (index == 0) {
            pRoot = pRoot->pPrev;
            destroyVideo(pRem);
            std::cout << "Первый элемент удален\n";
        }
        else {
            int num = 0;
            Video* pCur = pRoot;
            while (num < index) {
                if (pRem->pPrev == nullptr) {
                    std::cout << "Ошибка! Номер слишком большой, такой записи нет\n";
                    return;
                }
                pCur = pRem;
                pRem = pRem->pPrev;
                num++;
            }

            pCur->pPrev = pRem->pPrev;
            destroyVideo(pRem);
            std::cout << "Видео удалено.\n";
        }
    }

    void VideoManager::addVideos(){
        Video* pNew = createVideo();

        std::cout << "Введите название видео:\n>";
        std::cin.getline(pNew->title, sizeof(pNew->title));

        std::cout << "Введите автора:\n>";
        std::cin.getline(pNew->author, sizeof(pNew->author));

        std::cout << "Укажите кол-во лайков:\n>";
        std::cin >> pNew->likes;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера после ввода числа

        pNew->pPrev = pRoot; // добавляем указатель на последнюю добавленную запись до этой
        pRoot = pNew; // делаем pRoot последней добавленной записью

        std::cout << "Видео добавлено!\n";
    }
    
    void VideoManager::displayVideos() {
        Video* video = pRoot; // Указатель на отображаемую карточку видео
        int i = 1; // Номер карточки видео

        std::cout << " № | Название        | Автор         | Лайки |\n";
        std::cout << "---+-----------------+---------------+-------+\n";

        while (video) // Пока есть видео, выводим их на экран
        {
            std::cout << "\n";
            std::cout << std::setw(2) << std::right << i << " "; // Номер
            std::cout << "| " << std::setw(16) << std::left << video->title; // Название
            std::cout << "| " << std::setw(15) << std::left << video->author; // автор
            std::cout << "| " << std::setw(7) << std::right << video->likes << " "; // лайки
            
            video = video->pPrev;
            i++;
        }
        std::cout << "\n";
        if (i == 1)
        {
            std::cout << "Нет видео для отображения\n";
        }
    }

    void VideoManager::removeAll() {
        Video* pRem;
        while (pRoot != nullptr) {   // Пока есть записи
            pRem = pRoot; // Записываем в удаляемую переменную найденную запись
            pRoot = pRoot->pPrev;  // Переходим к следующей
            destroyVideo(pRem);   // Освобождаем память, удаляя карточку
        }
        pRoot = nullptr;
    }


}
