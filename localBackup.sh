#!/bin/bash

cartella=$1
descrizione=$2

git add $cartella
git commit -m $descrizione

