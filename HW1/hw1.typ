#import emoji: arrow

#align(center, text(17pt)[
  *Operating-system homework\#1*
])
#(text(14pt)[
= Written exercises
])

= • Chap.1
- 1.16: Direct memory access is used for high-speed I/O devices in order to avoid increasing the CPU's execution load.

  - (a) How does the CPU interface with the device to coordinate the transfer?

    Use DMA controller to coordinate the transfer

  - (b) How does the CPU know when the memory operations are complete?

    DMA will send an interrupt to the CPU when the memory operations are complete.

  - (c) The CPU is allowed to execute other programs while the DMA controller is transferring data. Does this process interfere with the execution of the user programs? If so, describe what forms of interference are caused.

    Yes.\
    If the CPU and the DMA need to share the same memory, it will reduced performance for the user programs because the CPU and the DMA will compete for the memory.


= • Chap. 2
- 2.15: What are the two models of interprocess communication? What are the strengths and weakness of the two approaches?
  the message-passing model and the shared-memory model.
  - message-passing -> pipes
    - Strengths: 
      - Easy to manage.
    - Weakness:
      - Slow than shared-memory
  - shared-memory -> shared memory
    - Strengths: 
      - Fast than message-passing
    - Weakness:
      - Not easy to manage because everyone can use the shared memory. 


- 2.19: What is the main advantage of the microkernel approach to system design? How do user programs and system services interact in a microkernel architecture? What are the disadvantages of using the microkernel approach?
  - Main advantage:
    - The main advantage of the microkernel approach to system design is that it is more modular and easier to customize.
  - How do user programs and system services interact in a microkernel architecture?
    - They interact through message passing.
    #figure(
      image("./image/micokernel.png",width: 50%)
    )
  - Disadvantages:
    - The modular design can make it more difficult to develop and maintain the operating system


= • Chap. 3
- 3.12: Describe the actions taken by a kernel to context-switch between processes.
Save the Current Process State to PCB-> Select the Next Process 
    #figure(
      image("./image/context-switch.png",width: 50%)
    )

- 3.18: Give an example of a situation in which ordinary pipes are more suitable than named pipes and an example of a situation in which named pipes are more suitable than ordinary pipes.
  - Ordinary Pipes : one-way communication channel \
    - ex. A parent process spawns multiple child processes and needs to implement a pipeline where the output of one child process serves as the input to the next child process.
    #grid(
      columns: (0.5fr, 1fr, 0.5fr, 1fr, 0.5fr),
      align: center + horizon,
      rect( width: 120%)[Parent],
      arrow.r.filled,
      rect( width: 120%)[child],
      arrow.r.filled,
      rect( width: 120%)[child]
    )
    
  - Named Pipes : bi-directional communication channel
    -  ex. Two independent processes running on the same system need to communicate with each other over a persistent, bi-directional channel.
    #grid(
      columns: (0.5fr, 1fr, 0.5fr),
      align: center + horizon,
      rect( width: 120%)[process],
      grid(
        columns: (1fr),
        align: center + horizon,
        arrow.r.filled,
        arrow.r.filled,
      ),
      rect( width: 120%)[process],
    )