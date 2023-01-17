# Motor-Testing-Fixture
This is project is a Motor Driver Shield for the L298N that I designed to use as a motor testing fixture. It can run up to 6 motors at once.
The nature of the testing was lifecycle testing so the PCB has a built-in counter feature that counts the number of cycles the motors have 
been running for. The entire fixture consists of the PCB design that is included, a counter, and then an Arduino to run the Motor test fixture code. 
The code also contains current sensing so once a motor has died, the fixture will stop until the motor has been removed or replaced and the fixture 
is restarted. 
