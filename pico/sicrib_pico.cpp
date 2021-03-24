/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "arduinoFFT.h"
#include <math.h>

#define RAW_SAMPLES 512	
// #define AVG_SAMPLES 1024
#define CLOCK_DIV 960
#define CAPTURE_CHANNEL 0
#define NUMBER_OF_BINS 10

arduinoFFT FFT = arduinoFFT();
dma_channel_config cfg;
uint dma_chan;

int sampling_freq = 50000;
// int number_of_samples_per_average = 2;
float freq_res = sampling_freq / (float) RAW_SAMPLES; //(float) AVG_SAMPLES;
float freqs[RAW_SAMPLES]; //AVG_SAMPLES];

void setup();
void sample(uint16_t*);


int freq_bins_lower[] = {0, 60, 250, 800, 1500, 2500, 4000, 4300, 4700, 5250};
int freq_bins_upper[] = {60, 250, 800, 1500, 2500, 4000, 4300, 4700, 5250, 6000};
double final_bins[NUMBER_OF_BINS];
// double last = microseconds();


int main() {

    sleep_ms(2000);

    setup();
    
    uint16_t capture_buffer[RAW_SAMPLES];
    double vReal[RAW_SAMPLES];//AVG_SAMPLES];
    double vImag[RAW_SAMPLES];//AVG_SAMPLES];

    while (1) {
        sample(capture_buffer);
        
        int sum = 0;
        for (int i = 0; i < RAW_SAMPLES; i++) {
            sum += capture_buffer[i];
        }
        double dc_offset = (double) sum / RAW_SAMPLES;
        
        
        for (int i = 0; i < RAW_SAMPLES; i++) { //AVG_SAMPLES; i++) {
        
            /*int sum = 0;
            for (int j = 0; j < number_of_samples_per_average; j++)
                sum += capture_buffer[number_of_samples_per_average * i + j];
            
            // double val = (double) sum / (double) SAMPLE_NUM_AVG - dc_offset;
            double val = (double) sum / number_of_samples_per_average - dc_offset;
            //printf("val %f\n", val);*/
            
            double val = capture_buffer[i] - dc_offset;
            
            vReal[i] = val;
            vImag[i] = 0.0;
            
        }
        
        
        
        FFT.Windowing(vReal, RAW_SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //AVG_SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, RAW_SAMPLES, FFT_FORWARD); //AVG_SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, RAW_SAMPLES); //AVG_SAMPLES);

        
        for (int i = 0; i < NUMBER_OF_BINS; i++) final_bins[i] = 0;
        
        int higher_order_bin = 0;
        int count = 0;
        for (int bin = 0; bin < RAW_SAMPLES; bin++) { //AVG_SAMPLES; bin++) {
        	if (freqs[bin] > freq_bins_upper[higher_order_bin]) {
        		final_bins[higher_order_bin] /= count;
        		count = 0;
        		higher_order_bin++;}
        	if (higher_order_bin >= NUMBER_OF_BINS) break;
        	count++;
        	final_bins[higher_order_bin] += vReal[bin];
        } 
        
        for (int i = 0; i < NUMBER_OF_BINS; i++) final_bins[i] = log10(final_bins[i]);
        
        /*printf("Time: %f\n", microseconds() - last);
        last = microseconds();*/
        //for (int i = 0; i < NUMBER_OF_BINS; i++) printf("%d - %d Hz: %f\n", freq_bins_lower[i], freq_bins_upper[i], final_bins[i]);
        printf("%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\n", final_bins[0], final_bins[1], final_bins[2], final_bins[3], final_bins[4], final_bins[5], final_bins[6], final_bins[7], final_bins[8], final_bins[9]);
        
        
    }
}

void setup() {
    // force ADC supply into PWN mode for less noise
    gpio_init(23);
    gpio_set_dir(23, GPIO_OUT);
    gpio_put(23, 1);
    stdio_init_all();
    
    adc_gpio_init(26 + CAPTURE_CHANNEL);
    adc_init();
    sleep_ms(1000);
    adc_select_input(CAPTURE_CHANNEL);
    adc_fifo_setup(true, true, 1, false, false);
    adc_set_clkdiv(CLOCK_DIV);
    
    uint dma_chan = dma_claim_unused_channel(true);
    cfg = dma_channel_get_default_config(dma_chan);
    
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_16);
    channel_config_set_read_increment(&cfg, false);
    channel_config_set_write_increment(&cfg, true);
    
    channel_config_set_dreq(&cfg, DREQ_ADC);
    for (int i = 0; i < RAW_SAMPLES; i++) /*AVG_SAMPLES; i++)*/ freqs[i] = freq_res * i;
    
}


void sample(uint16_t *capture_buf) {
    //adc_fifo_drain();
    adc_run(false);
    dma_channel_configure(dma_chan, &cfg, capture_buf, &adc_hw->fifo, RAW_SAMPLES, true);
    adc_run(true);
    dma_channel_wait_for_finish_blocking(dma_chan);
}
