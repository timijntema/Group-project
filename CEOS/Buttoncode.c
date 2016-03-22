#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

//Het aansluiten is vanaf GPIO #26 omhoog beginnend met de losstaande knop op #26
//Je moet ergens rond de 2e ground van onder een pin overslaan want die deed het bij mij niet

//Deze code geeft een array met 1en en 0len terug

// Button inputs
#define PIN1 RPI_GPIO_P1_15
#define PIN2 RPI_V2_GPIO_P1_19
#define PIN3 RPI_V2_GPIO_P1_21 
#define PIN4 RPI_V2_GPIO_P1_23
#define PIN5 RPI_V2_GPIO_P1_29
#define PIN6 RPI_BPLUS_GPIO_J8_31
#define PIN7 RPI_V2_GPIO_P1_33
#define PIN8 RPI_V2_GPIO_P1_35
#define OKPIN RPI_V2_GPIO_P1_37

#define ARRAY_SIZE 8

void init(int pin, int inofout){
    if (inofout == 1){
        //create pin set it to input and add a resistor
       bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
       bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP);
    }
    else if (inofout == 0){
        //create pin as output
        bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);//nog checken
    }
}
void get_input(int new_array[ARRAY_SIZE]){
    
    // Set pins as output
    init(PIN1,1);
    init(PIN2,1);
    init(PIN3,1);
    init(PIN4,1);
    init(PIN5,1);
    init(PIN6,1);
    init(PIN7,1);
    init(PIN8,1);
    init(OKPIN,1);
    
    /*sbcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PIN3, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PIN4, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PIN5, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PIN6, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PIN7, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PIN8, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(OKPIN, BCM2835_GPIO_FSEL_INPT);*/
    
    
    
    // Create pullup resistors on all pins
    /*bcm2835_gpio_set_pud(PIN1, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(PIN2, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(PIN3, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(PIN4, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(PIN5, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(PIN6, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(PIN7, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(PIN8, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(OKPIN, BCM2835_GPIO_PUD_UP);*/
    
    
    // start checking for input
    while (1)
    {
        // Read data
        if (bcm2835_gpio_lev(PIN1) != 1){
            new_array[0] = 1;
            sleep(0.5);  
        }
        else if (bcm2835_gpio_lev(PIN2) != 1){
            new_array[1] = 1;
            sleep(0.5);
        }
        else if (bcm2835_gpio_lev(PIN3) != 1){
            new_array[2] = 1;
            sleep(0.5);
        }
        else if (bcm2835_gpio_lev(PIN4) != 1){
            new_array[3] = 1;
            sleep(0.5);
        }
        else if (bcm2835_gpio_lev(PIN5) != 1){
            new_array[4] = 1;
            sleep(0.5);
        }
        else if (bcm2835_gpio_lev(PIN6) != 1){
            new_array[5] = 1;
            sleep(0.5);
        }
        else if (bcm2835_gpio_lev(PIN7) != 1){
            new_array[6] = 1;
            sleep(0.5);
        }
        else if (bcm2835_gpio_lev(PIN8) != 1){
            new_array[7] = 1;
            sleep(0.5);
        }
        if (bcm2835_gpio_lev(OKPIN) != 1){
            break;
        }
    }
}


int main(int argc, char **argv)
{
    //check if bcm2835 has initialized
    if (!bcm2835_init()){
        return 1;
    }
    //create array size
    int new_array[ARRAY_SIZE] = {0,0,0,0,0,0,0,0};
    
    get_input(new_array);
    
    
    int i;
    for (i = 0; i<ARRAY_SIZE; i++){
        printf("%d\n", new_array[i]);
    }
    //close the bcm2835 library
    bcm2835_close();
    return 0;
}
