#!/bin/bash
echo $((2 && 0))
echo $((4 && 1))
echo $((3 || 0))
echo $((0 || 0))
