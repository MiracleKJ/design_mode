//
// Created by logan on 18-5-26.
//

#include <iostream>
#include <string>
#include <memory>

class MediaPlayer
{
public:
    virtual void Play(const std::string& audio_type,const std::string& file_name) = 0;
};

class AdvancedMediaPlayer
{
public:
    virtual void PlayVlc(const std::string& file_name) = 0;
    virtual void PlayMp4(const std::string& file_name) = 0;
};

class VlcPlayer : public AdvancedMediaPlayer
{
public:
    void PlayVlc(const std::string& file_name)
    {
        std::cout << "Playing vlc file. Name: " << file_name << std::endl;
    }

    void PlayMp4(const std::string& file_name)
    {}
};

class Mp4Player : public AdvancedMediaPlayer
{
public:
    void PlayVlc(const std::string& file_name)
    {}

    void PlayMp4(const std::string& file_name)
    {
        std::cout << "Playing mp4 file. Name: " << file_name << std::endl;
    }
};

class MediaAdapter : public MediaPlayer
{
public:
    MediaAdapter() = delete;
    MediaAdapter(const std::string& audio_type)
            : advanced_media_player_(nullptr)
    {
        if ("vlc" == audio_type)
        {
            advanced_media_player_ = std::make_unique<VlcPlayer>();
        }
        else if ("mp4" == audio_type)
        {
            advanced_media_player_ = std::make_unique<Mp4Player>();
        }
    }

    void Play(const std::string& audio_type,const std::string& file_name)
    {
        if ("vlc" == audio_type)
        {
            advanced_media_player_->PlayVlc(file_name);
        }
        else if ("mp4" == audio_type)
        {
            advanced_media_player_->PlayMp4(file_name);
        }
    }

private:
    std::unique_ptr<AdvancedMediaPlayer> advanced_media_player_;
};

class AudioPlayer : public MediaPlayer
{
public:
    void Play(const std::string& audio_type,const std::string& file_name)
    {
        if ("mp3" == audio_type)
        {
            std::cout << "Play mp3" << std::endl;
        }
        else if ("vlc" == audio_type || "mp4" == audio_type)
        {
            media_adapter_ = std::make_unique<MediaAdapter>(audio_type);
            media_adapter_->Play(audio_type, file_name);
        }
        else
        {
            std::cout << "Invalid media. " << audio_type << " format not supported" << std::endl;
        }
    }

private:
    std::unique_ptr<MediaAdapter> media_adapter_;
};

int main(int argc, char *argv[])
{
    AudioPlayer audio_player;

    audio_player.Play("mp3","1.mp3");
    audio_player.Play("mp4","1.mp4");
    audio_player.Play("vlc","1.vlc");
    audio_player.Play("avi","1.avi");

    return 1;
}