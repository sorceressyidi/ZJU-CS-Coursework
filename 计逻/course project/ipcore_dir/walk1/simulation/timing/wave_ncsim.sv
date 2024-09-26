
 
 
 

 



window new WaveWindow  -name  "Waves for BMG Example Design"
waveform  using  "Waves for BMG Example Design"


      waveform add -signals /walk1_tb/status
      waveform add -signals /walk1_tb/walk1_synth_inst/bmg_port/CLKA
      waveform add -signals /walk1_tb/walk1_synth_inst/bmg_port/ADDRA
      waveform add -signals /walk1_tb/walk1_synth_inst/bmg_port/DOUTA
console submit -using simulator -wait no "run"
