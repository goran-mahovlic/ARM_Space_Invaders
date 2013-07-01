ARM_Space_Invaders from http://www.artekit.eu/
==================

Using the previous VGA output project [http://www.artekit.eu/vga-output-using-a-36-pin-stm32/], we have created this Space Invaders version for STM32.

The source code is kept as a separated project, but uses the same engine of the VGA output project.

The project is in KEIL uVision format. 

You can download the KEIL uVision evaluation version from www.keil.com

Here is a video of the results:
http://www.youtube.com/watch?feature=player_embedded&v=Eq9p5guqQ-g

Connections
We have added three push-buttons to the original connections. These push-buttons serve as a joystick.

Here are the connections for the push-buttons and the VGA connector:



AK-STM32-LKIT pin	VGA connector pin	Push-button	Edit
PA1	Pin 14		Vertical Sync
PA7	Pin 2		Green
PA8	Pin 13		Horizontal Sync
PA5		K1	Left button
PA4		K2	Right button
PA0		K3	Fire button

Have fun!

http://www.artekit.eu/space-invaders-for-stm32/