#pragma once
#ifndef FILEWORK_H
#define FILEWORK_H
#include <string>
struct Video {
    char title[100];
    char author[100];
    int likes;
    Video* pPrev; //указатель на предыдущее видео

    friend std::ostream& operator<<(std::ostream& os, const Video& video);
    friend std::istream& operator>>(std::istream& is, Video& video);
};

std::ostream& operator<<(std::ostream& os, const Video& video);
std::istream& operator>>(std::istream& is, Video& video);

namespace VideoLibrary {
    class VideoManager {
    private:
        Video* pRoot; //последнее добавленное видео
        const char* const VideoFile;

        //Вспомогательные функции
        Video* createVideo(); // выделяем память
        void destroyVideo(Video* video); // освобождаем память

    public:
        VideoManager(const char* filename);
        ~VideoManager();
        void addVideos();     // Добавление видео
        void loadVideos();    // Загрузка видео
        void saveVideos();    // Сохранение видео
        void displayVideos(); // Вывести список видео на экране
        void deleteVideos();  // Удаление видео
        void removeAll();     // Удалить всё из памяти
    };

} 
#endif

