#include <fstream>
#include <iostream>
#include <string>

#include "core.h"

#define OUTPUT_WAV_NAME "audio.wav"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid argument" << std::endl;
        return 0;
    }

    std::string open_jtalk_dict_path(argv[1]);
    std::string text(argv[2]);

    std::cout << "coreの初期化中..." << std::endl;

    if (!initialize(false))
    {
        std::cout << "coreの初期化に失敗しました" << std::endl;
        return 1;
    }

    VoicevoxResultCode result;

    std::cout << "openjtalk辞書の読み込み中..." << std::endl;

    result = voicevox_load_openjtalk_dict(open_jtalk_dict_path.c_str());
    if (result != VOICEVOX_RESULT_SUCCEED)
    {
        std::cout << voicevox_error_result_to_message(result) << std::endl;
        return 1;
    }

    std::cout << "音声生成中..." << std::endl;

    int64_t speaker_id = 1;
    int output_binary_size = 0;
    uint8_t *output_wav = nullptr;

    result = voicevox_tts(text.c_str(), speaker_id, &output_binary_size, &output_wav);
    if (result != VOICEVOX_RESULT_SUCCEED)
    {
        std::cout << voicevox_error_result_to_message(result) << std::endl;
        return 1;
    }

    std::cout << "音声ファイル保存中..." << std::endl;

    std::ofstream wav_file(OUTPUT_WAV_NAME, std::ios::binary);
    wav_file.write(reinterpret_cast<const char *>(output_wav), output_binary_size);
    voicevox_wav_free(output_wav);

    std::cout << "音声ファイル保存完了 (" << OUTPUT_WAV_NAME << ")" << std::endl;

    return 0;
}