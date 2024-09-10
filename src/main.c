#include <rtl-sdr.h>

#include <stdio.h> 
#include <signal.h>
#include <stdlib.h>

#define ADSB_RATE 2048000
#define ADSB_FREQ 1090000000

static rtlsdr_dev_t *dev = NULL;

void INThandler(int sig) { 
    rtlsdr_cancel_async(dev);
}

void rx_cb(unsigned char* buf, uint32_t len, void *ctx) { 
    // process received samples
    // printing num of samples for now
    printf("Received %u samples\n", len);
}

int main() { 
    int dev_index = 0;
    int ret;

    // Initialize rtl device
    ret = rtlsdr_open(&dev, dev_index);
    if (ret < 0) { 
        fprintf(stderr, "Failed to open RTL-SDR device\n");
        return 1;
    }

    // Set sample rate
    ret = rtlsdr_set_sample_rate(dev, ADSB_RATE);
    if (ret < 0) { 
        fprintf(stderr, "Failed to set sample rate\n");
        rtlsdr_close(dev);
        return 1;
    }

    // Set freq
    ret = rtlsdr_set_center_freq(dev, ADSB_FREQ);
    if (ret < 0) { 
        fprintf(stderr, "Failed to set frequency\n");
        rtlsdr_close(dev);
        return 1;
    }

    // Start receiving samples asynchronously
    signal(SIGINT, INThandler);
    ret = rtlsdr_read_async(dev, rx_cb, NULL, 0, 0);

    rtlsdr_close(dev);

    printf("exiting...\n");

    return 0;
}