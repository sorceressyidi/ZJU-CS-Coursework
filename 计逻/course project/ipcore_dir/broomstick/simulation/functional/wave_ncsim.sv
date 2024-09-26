

 
 
 

 



window new WaveWindow  -name  "Waves for BMG Example Design"
waveform  using  "Waves for BMG Example Design"

      waveform add -signals /broomstick_tb/status
      waveform add -signals /broomstick_tb/broomstick_synth_inst/bmg_port/CLKA
      waveform add -signals /broomstick_tb/broomstick_synth_inst/bmg_port/ADDRA
      waveform add -signals /broomstick_tb/broomstick_synth_inst/bmg_port/DINA
      waveform add -signals /broomstick_tb/broomstick_synth_inst/bmg_port/WEA
      waveform add -signals /broomstick_tb/broomstick_synth_inst/bmg_port/DOUTA

console submit -using simulator -wait no "run"
