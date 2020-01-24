# Gardener

## Version

v0.0

## Description

Prototype implementation plant gardener.  Waters a plant with an on-board DC
pump for a fixed period of time after another fixed period of time elapses.

## Design

Finite state machine run in a null task loop.  The Gardener State Machine (GSM)
is serviced alongside constituent components' state machines.  Constituent
components are timer, configuration manager, and pump motor controller.

*SDG*
