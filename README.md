# Linnaeo: a protein sequence comparison tool

![Screenshot](docs/images/screenshot_main.png)

Linnaeo is a program designed to help draw conclusions about the structure-function relationship of proteins by providing an easy way to compare protein sequences. Often a protein that is well-studied in one organism (maybe the structure is known, or it has been studied enzymatically quite a bit) is not well understood in your species of interest. Making alignments can help you find equivalent residues to those that are characterized in these alternative protein sequences, as well as suggest other residues that are important based on how highly they are conserved. Linnaeo is therefore designed to allow you to:
 * Store and organize protein sequences you want to keep track of in folders
 * Generate (and organize) alignments dynamically from different combinations of those sequences using the MUSCLE algorithm
 * Color by residue type, conservation, or identity to a reference sequence
 * Export these alignments for use in other favorite alignment viewers
 
 
 
 TODO (long term): 
  * Add a QTableView with a list of important residues (will probably need a database). Show below sequence browser
  * Use latter for "Translator" between two proteins. 
