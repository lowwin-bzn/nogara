#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <vorbis/vorbisfile.h>
#include <cstdio>
#include <unistd.h>
#define NUM_BUFFERS 32
#define BUFFER_SIZE 4096
#ifdef __BIG_ENDIAN__
#define ENDIAN 1
#else
#define ENDIAN 0
#endif

int main(int argc, char *argv[0]){
    ALCdevice *device;
    ALCcontext *context;
    ALuint source, buffer;
    ALint state, n;
    int i;
    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    alGenSources(1, &source);
    for (i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "rb");
        OggVorbis_File vf;
        int current = 0;
        ov_open(fp, &vf, NULL, 0);
        std::cout << 
        for (;;) {
            char data[BUFFER_SIZE];
            long size = ov_read(&vf, data, sizeof(data), ENDIAN, 2, 1, &current);
            vorbis_info *info = ov_info(&vf, -1);
            ALenum format = info->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
            if (size <= 0) {
                break;
            }
            alGetSourcei(source, AL_BUFFERS_QUEUED, &n);
            if (n < NUM_BUFFERS) {
                alGenBuffers(1, &buffer);
            } else {
                alGetSourcei(source, AL_SOURCE_STATE, &state);
                if (state != AL_PLAYING) {
                    alSourcePlay(source);
                }
                while (alGetSourcei(source, AL_BUFFERS_PROCESSED, &n), n == 0) { 
                    usleep(1000);
                }
                alSourceUnqueueBuffers(source, 1, &buffer);
            }
            alBufferData(buffer, format, data, size, info->rate);
            alSourceQueueBuffers(source, 1, &buffer);
        }
        ov_clear(&vf);
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING) {
            alSourcePlay(source);
        }
        while (alGetSourcei(source, AL_SOURCE_STATE, &state), state == AL_PLAYING) {
            usleep(1000);
        }
        while (alGetSourcei(source, AL_BUFFERS_PROCESSED, &n), n > 0) {
            alSourceUnqueueBuffers(source, 1, &buffer);
            alDeleteBuffers(1, &buffer);
        }
    }
    alDeleteSources(1, &source);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
    return 0;
}
