#include "stdafx.h"
#include "Editor.h"
#include <fstream>
#include "stdafx.h"
#include <SDL2/SDL.h>
#include "sdl2.h"
int sdl_loop(Editor &editor){
    SDL_Event event;
    bool quit = false;
    while (!quit){
        SDL_PumpEvents();
        editor.Run();
        int ret = SDL_PollEvent(&event);
        if (ret < 0) {
            std::cerr << "Error Peeping event: " << SDL_GetError() << std::endl;
            std::cerr << "Exiting now" << std::endl;
            return -1;}
        if (ret > 0) {
            if (event.type == SDL_WINDOWEVENT) {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_CLOSE: {  // exit game:editor.Quit();
                        quit = true;}
                    default:{break;}}}}}
    return 0;}
#include <alsa/asoundlib.h>
#include <iostream>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>

#define BUFSIZE 1024

/* A simple routine calling UNIX write() in a loop */
static ssize_t loop_write(int fd, const void*data, size_t size) {
    ssize_t ret = 0;

    while (size > 0) {
        ssize_t r;

        if ((r = write(fd, data, size)) < 0)
            return r;

        if (r == 0)
            break;

        ret += r;
        data = (const uint8_t*) data + r;
        size -= (size_t) r;
    }

    return ret;
}

int main2(int argc, char*argv[]) {
    /* The sample type to use */
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 2
    };
    pa_simple *s = NULL;
    int ret = 1;
    int error;

    /* Create the recording stream */
    if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        goto finish;
    }

    for (;;) {
        uint8_t buf[BUFSIZE];

        /* Record some data ... */
        if (pa_simple_read(s, buf, sizeof(buf), &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
            goto finish;
        }

        /* And write it to STDOUT */
        if (loop_write(STDOUT_FILENO, buf, sizeof(buf)) != sizeof(buf)) {
            fprintf(stderr, __FILE__": write() failed: %s\n", strerror(errno));
            goto finish;
        }
    }

    ret = 0;

finish:

    if (s)
        pa_simple_free(s);

    return ret;
}
// Globals are generally a bad idea in code.  We're using one here to keep it simple.v
int i;
int err;
snd_pcm_hw_params_t *hw_params;
snd_pcm_t * _soundDevice;
unsigned int resample = 1; ;
unsigned int actualRate = 44100;// Set sample rate.
int main(int argc, char *argv[]){

    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 2
    };
    pa_simple *s = NULL;
    int ret1 = 1;
    int error;

    /* Create the recording stream */
    if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        goto finish;
    }
	else{printf("pulsepoint found\n");}

finish:
    if (s){pa_simple_free(s);}
    if(false){
        using namespace std;
    	if( true ){// Try to open the default device
    						err = snd_pcm_open( &_soundDevice, "plughw:0,0", SND_PCM_STREAM_PLAYBACK, 0 );}
    	else{// Open the device we were told to open.
    						err = snd_pcm_open (&_soundDevice, NULL, SND_PCM_STREAM_PLAYBACK, 0);}
    	if( err < 0 ){// Check for error on open.
    						cout << "Init: cannot open audio device " <<NULL << " (" << snd_strerror (err) << ")" << endl;
    						return false;}
    	else{cout << "Audio device opened successfully." << endl;}
    	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0){// Allocate the hardware parameter structure.
    						cout << "Init: cannot allocate hardware parameter structure (" << snd_strerror (err) << ")" << endl;
    						return false;}
    	if ((err = snd_pcm_hw_params_any (_soundDevice, hw_params)) < 0){
    						cout << "Init: cannot initialize hardware parameter structure (" << snd_strerror (err) << ")" << endl;
    						return false;}
    	if ((err = snd_pcm_hw_params_set_rate_resample(_soundDevice, hw_params, resample)) < 0){
    						cout << "Init: Resampling setup failed for playback: " << snd_strerror(err) << endl;
    						return err;}  
    	if ((err = snd_pcm_hw_params_set_access (_soundDevice, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0){// Set access to RW interleaved.
    						cout << "Init: cannot set access type (" << snd_strerror (err) << ")" << endl;
    						return false;}
    	if ((err = snd_pcm_hw_params_set_format (_soundDevice, hw_params, SND_PCM_FORMAT_S16_LE)) < 0){
    						cout << "Init: cannot set sample format (" << snd_strerror (err) << ")" << endl;
    						return false;}
    	if ((err = snd_pcm_hw_params_set_channels (_soundDevice, hw_params, 2)) < 0){// Set channels to stereo (2).
    						cout << "Init: cannot set channel count (" << snd_strerror (err) << ")" << endl;
    						return false;}
    	if ((err = snd_pcm_hw_params_set_rate_near (_soundDevice, hw_params, &actualRate, 0)) < 0){
    						cout << "Init: cannot set sample rate to 44100. (" << snd_strerror (err) << ")"  << endl;
    						return false;}
    	if( actualRate < 44100 ){cout << "Init: sample rate does not match requested rate. (" << "44100 requested, " << actualRate << " acquired)" << endl;}
    	if ((err = snd_pcm_hw_params (_soundDevice, hw_params)) < 0){// Apply the hardware parameters that we've set.
    						cout << "Init: cannot set parameters (" << snd_strerror (err) << ")" << endl;
    						return false;}
    	else{cout << "Audio device parameters have been set successfully." << endl;}
    	snd_pcm_uframes_t bufferSize;  // Get the buffer size.
    	snd_pcm_hw_params_get_buffer_size( hw_params, &bufferSize );// If we were going to do more with our sound device we would want to store
    	//   cout << "Init: Buffer size = " << bufferSize << " frames." << endl;  // the buffer size so we know how much data we will need to fill it with.
    	//   cout << "Init: Significant bits for linear samples = " << snd_pcm_hw_params_get_sbits(hw_params) << endl;  // Display the bit size of samples.
    	snd_pcm_hw_params_free (hw_params);// Free the hardware parameters now that we're done with them.
    	if ((err = snd_pcm_prepare (_soundDevice)) < 0){// Prepare interface for use.
    						cout << "Init: cannot prepare audio interface for use (" << snd_strerror (err) << ")" << endl;
    						return false;}
    	else{cout << "Audio device has been prepared for use." << endl;}}
    Editor editor;
    wiStartupArguments::Parse(argc, argv);
    sdl2::sdlsystem_ptr_t system = sdl2::make_sdlsystem(SDL_INIT_EVERYTHING | SDL_INIT_EVENTS);
    if (!system) {throw sdl2::SDLError("Error creating SDL2 system");}
    sdl2::window_ptr_t window = sdl2::make_window(//TODO read config.ini
            "Wicked Engine Editor",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            1920, 1080,
            SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
    if (!window) {throw sdl2::SDLError("Error creating window");}
    editor.SetWindow(window.get());
    int ret = sdl_loop(editor);
    SDL_Quit();
    return ret;}