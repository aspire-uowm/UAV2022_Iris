#include "./example/driver_nrf24l01_basic.h"

uint8_t (*g_gpio_irq)(void) = NULL;
uint8_t res;
uint32_t timeout;


static void a_callback(uint8_t type, uint8_t num, uint8_t *buf, uint8_t len)
{
    switch (type)
    {
        case NRF24L01_INTERRUPT_RX_DR :
        {
            uint8_t i;
            

            nrf24l01_interface_debug_print("nrf24l01: irq receive with pipe %d with %d.\n", num, len);
            for (i = 0; i < len; i++)
            {
                nrf24l01_interface_debug_print("0x%02X ", buf[i]);
            }
            nrf24l01_interface_debug_print(".\n");
            
            break;
        }
        case NRF24L01_INTERRUPT_TX_DS :
        {
            nrf24l01_interface_debug_print("nrf24l01: irq sent ok.\n");
            
            break;
        }
        case NRF24L01_INTERRUPT_MAX_RT :
        {
            nrf24l01_interface_debug_print("nrf24l01: irq reach max retry times.\n");
            
            break;
        }
        case NRF24L01_INTERRUPT_TX_FULL :
        {
            break;
        }
        default :
        {
            break;
        }
    }

}

int main(int argc, char const *argv[]){
    timeout = 5000;
    
    res = gpio_interrupt_init();
    
    if (res != 0)return 1;
    
    g_gpio_irq = nrf24l01_interrupt_irq_handler;
    res = nrf24l01_basic_init(NRF24L01_TYPE_RX, a_callback);
    
    if (res != 0){
        (void)gpio_interrupt_deinit();
        g_gpio_irq = NULL;

        return 1;
    }

    nrf24l01_interface_delay_ms(timeout);
    if (nrf24l01_basic_deinit() != 0){
        (void)gpio_interrupt_deinit();
        g_gpio_irq = NULL;

        return 1;
    }

    (void)gpio_interrupt_deinit();
    g_gpio_irq = NULL;

    return 0;
}
