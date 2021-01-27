## THEMES

Linnaeo provides a variety of different themes for displaying amino acid properties in the sequence viewer. 
This document is designed to provide a deeper explanation for the meaning behind what these color schemes represent.

---
### Linnaeo default theme

The default theme was partially inspired by Clustal X categories but with colors that were intended to be as easily readable as possible. Although not necessarily the best for quickly seeing unusual residues or differences, it may perhaps be the easiest on the eyes. 

Colors used for the default theme: 

<span style="background-color: #97A4E8; color: #000000">Hydrophobic</span>, 
<span style="background-color: #A0EDD8; color: #000000">Aromatic</span>, 
<span style="background-color: #BEF1AC; color: #000000">Polar</span>, 
<span style="background-color: #F2F0B5; color: #000000">Cysteine</span>, 
<span style="background-color: #F4D5BE; color: #000000">Proline</span>, 
<span style="background-color: #DB8A8B; color: #000000">Positive</span>, 
<span style="background-color: #E190E2; color: #000000">Negative</span>, 
<span style="background-color: #F1EBD5; color: #000000">Alanine</span>, 
<span style="background-color: #E0E0E0; color: #000000">Glycine</span>

Residues are organized into the following categories, based on property: 

|Hydrophobic|Aromatic|Polar|Positive|Negative|Misc|
|---|---|---|---|---|---|
|Leucine (L)|Tryptophan (W)|Serine (S)|Arginine (R)|Aspartate (D)|Cysteine (C)|
|Isoleucine (I)|Tyrosine (Y)|Threonine (T)|Lysine (K)|Glutamate (E)|Proline (P)
|Valine (V)|Phenylalanine (F)| Aspargine (N)|Histidine (H)||Alanine (A)|
|Methionine (M)||Glutamine (Q)|||Glycine (G)|

If conservation is turned on, the hydrophobic colors are also used for Alanine, Phenylalanine, Threonine, Tyrosine, or Tryptophan if the remaining residues are hydrophobic. 

This same organization is also used by the Colorsafe theme (<span style=" background-color: #97A4E8; color: #000000">Hydrophobic</span>, 
<span style=" background-color: #D1EFFF; color: #000000">Aromatic</span>, 
<span style=" background-color: #C892C9; color: #000000">Polar</span>, 
<span style=" background-color: #A6E8D6; color: #000000">Cysteine</span>, 
<span style=" background-color: #FEC8C8; color: #000000">Proline</span>, 
<span style=" background-color: #FFDCC2; color: #000000">Positive</span>, 
<span style=" background-color: #F0CD4C; color: #000000">Negative</span>, 
<span style=" background-color: #CCF4BE; color: #000000">Alanine</span>, 
<span style=" background-color: #E0E0E0; color: #000000">Glycine</span>), which is intended to be more color-blind friendly (please let me know if it is not!)

There is also a theme that replicates the color choices of Clustal X. This is very similar, but uses fewer colors and puts more in the hydrophobic category. 

---

### Hydropathy theme

This theme colors each individual amino acid based on its calculated preference for water by the Kyle-Doolittle scale. 
More information on this is available [here](http://resources.qiagenbioinformatics.com/manuals/clcgenomicsworkbench/650/Hydrophobicity_scales.html#:~:text=The%20Kyte%2DDoolittle%20scale%20is,on%20the%20window%20size%20used.) 
and [here](http://www.imgt.org/IMGTeducation/Aide-memoire/_UK/aminoacids/IMGTclasses.html).

The colors range in a continuous scale from magenta to aqua, via white, where magenta is the most hydrophobic and aqua is the most hydrophilic. Colors closer to white are more or less neutral in terms of hydropathy. 
[See the tool used to generate the colors here](https://bit.ly/2V8VF11).

||||||||
|---|---|---|---|---|---|---|
|<span style=" background-color: #cc2fba; color: #000000">&nbsp;Isoleucine&nbsp;</span>|<span style=" background-color: #d736c5; color: #000000">&nbsp;Valine&nbsp;</span>|<span style=" background-color: #e342d1; color: #000000">&nbsp;Leucine&nbsp;</span>|<span style=" background-color: #ee56dc; color: #000000">&nbsp;Phenylalanine&nbsp;</span>|<span style=" background-color: #f571e6; color: #000000">&nbsp;Cysteine&nbsp;</span>|<span style=" background-color: #fa98ef; color: #000000">&nbsp;Methionine&nbsp;</span>|<span style=" background-color: #fdc9f7; color: #000000">&nbsp;Alanine&nbsp;</span>|
|<span style=" background-color: #fee4fb; color: #000000">&nbsp;Tryptophan&nbsp;</span>|<span style=" background-color: #E0E0E0; color: #000000">&nbsp;Glycine&nbsp;</span>|<span style=" background-color: #cefdf9; color: #000000">&nbsp;Threonine&nbsp;</span>|<span style=" background-color: #cefdf9; color: #000000">&nbsp;Serine&nbsp;</span>|<span style=" background-color: #9efaf3; color: #000000">&nbsp;Tyrosine&nbsp;</span>|<span style=" background-color: #73f6eb; color: #000000">&nbsp;Proline&nbsp;</span>|<span style=" background-color: #50f0e3; color: #000000">&nbsp;Histidine&nbsp;</span>|||
|<span style=" background-color: #35e8d9; color: #000000">&nbsp;Asparagine&nbsp;</span>|<span style=" background-color: #21dece; color: #000000">&nbsp;Aspartate&nbsp;</span>|<span style=" background-color: #12d1c1; color: #000000">&nbsp;Glutamine&nbsp;</span>|<span style=" background-color: #09c2b3; color: #000000">&nbsp;Glutamate&nbsp;</span>|<span style=" background-color: #03b4a5; color: #000000">&nbsp;Lysine&nbsp;</span>|<span style=" background-color: #00a693; color: #000000">&nbsp;Arginine&nbsp;</span>|

---

