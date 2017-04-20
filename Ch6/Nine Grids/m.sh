#!/bin/bash
if [ -f "$1.md" ]
then
	mkdir "$1" && mv "$1".md "$1"/
fi
