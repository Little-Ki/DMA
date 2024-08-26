# DMA

This is just a small library which contains the basic support for your DMA including
- memory reading
- memory writing
- getting PID and Base Address

Feel free to modify the code or make it better. Replace the example dlls with your own dlls.

The program expects you to have the dlls FTD3XX.dll, leechcore.dll and vmm.dll (download them from your DMA supplier) at the root directory when shipping the program.

The project requires the leechcore.lib and vmm.lib libraries in the libs/ folder. I did not add the precompiled libraries for security purposes. 
View third_party folder to those repositories