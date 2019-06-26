#!/bin/bash

vm=./tools/filler_vm
my_player=./nboulif.filler

all_players="tools/players/abanlin.filler
tools/players/abarriel.filler
tools/players/carli.filler
tools/players/grati.filler
tools/players/hcao.filler
tools/players/superjeannot.filler"
# tools/players/ntoniolo.filler"
# tools/players/carodrig.filler
# tools/players/champely.filler
# tools/players/nboulif.filler
# tools/players/qhonore.filler
# tools/players/lcharvol.filler
# tools/players/hvromman.filler
# tools/players/rpousseu_last.filler
# tools/players/sofchami.filler 

all_maps="tools/maps/map00 
tools/maps/map01
tools/maps/map02"
#tools/maps/map03

run_games() {
	let index=0
	for player in $all_players; do
		# for map in tools/maps/map00 tools/maps/map01; do
		for map in  $all_maps; do
			# echo "Processing $index ${player##*/} vs ${player##*/} on map ${player##*/}"
			$vm -f ./$map -p1 ./$my_player -p2 ./$player | python3 visu/filler_visu.py 250 $index &
			let index++
			
			# echo "Processing ${player##*/} vs $index ${player##*/} on map ${player##*/}"
			$vm -f ./$map -p1 ./$player -p2 ./$my_player | python3 visu/filler_visu.py 250 $index &
			let index++
		done
	done
	read -p "Press enter to quit all"
	pkill -f filler
}

run_games
