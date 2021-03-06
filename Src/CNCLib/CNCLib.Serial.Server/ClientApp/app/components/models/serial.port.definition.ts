import { Component, Inject } from '@angular/core';

export class SerialPortDefinition {
    id: number;
    portName: string;
    isConnected: number;
    isAborted: number;
    isSingleStep: number;
    commandsInQueue: number;
}
