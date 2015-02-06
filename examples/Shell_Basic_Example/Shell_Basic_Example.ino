/**
 * SIMPLE EXAMPLE OF COMMAND SHELL LIBRARY
 * 
 * This library implements a command line interface. The experience is similar to the windows
 * command prompt. This library can invoke functions when a specific string is received, in this
 * example we register 2 commands that can be executed by typing their names on the arduino serial
 * monitor (using the hardware UART).
 * 
 * The "shell" library is designed to be independent of the communication channel, this means
 * that it can be used with serial, softSerial and even TCP connections. For this reason the
 * shell library requires 2 pointers to functions to read and write characters to and from the
 * physical transmission media.
 * 
 * Arguments can be passed to the programs that are invoked by the command line and parsed by
 * standard string parsing functions, or you can write your own functions. The arguments
 * are passed as pointers to characters (null terminated strings) in a similar way that you
 * would receive them on any command line tool written in C. Each parameter is separated by
 * a "space" character after the command name.
 */

#include <Shell.h>

void setup()
{
  // Prepare serial communication
  Serial.begin(9600);
  // Wait after reset or power on...
  delay(1000);

  // Initialize command line interface (CLI)
  // We pass the function pointers to the read and write functions that we implement below
  // We can also pass a char pointer to display a custom start message
  shell_init(shell_reader, shell_writer, 0);

  // Add commands to the shell
  shell_register(command_mycommand, "mycommand");
  shell_register(command_othercommand, "othercommand");
}

void loop()
{
  // This should always be called to process user input
  shell_task();
}

/**
 * Test commands: The commands should always use this function prototype.
 * They receive 2 parameters: The total count of arguments (argc) and a pointer 
 * to the begining of each one of the null-terminated argument strings.
 *
 + In this example we ignore the parameters passed to the functions
 */
int command_mycommand(int argc, char** argv)
{
  shell_println("Running \"mycommand\" now");
  shell_println("Exit...");
  return SHELL_RET_SUCCESS;
}

int command_othercommand(int argc, char** argv)
{
  shell_println("Running \"othercommand\" now");
  shell_println("Exit...");
  return SHELL_RET_SUCCESS;
}

/**
 * Function to read data from serial port
 * Functions to read from physical media should use this prototype:
 * int my_reader_function(char * data)
 */
int shell_reader(char * data)
{
  // Wrapper for Serial.read() method
  if (Serial.available()) {
    *data = Serial.read();
    return 1;
  }
  return 0;
}

/**
 * Function to write data to serial port
 * Functions to write to physical media should use this prototype
 * void my_writer_function(char data)
 */
void shell_writer(char data)
{
  // Wrapper for Serial.write() method
  Serial.write(data);
}