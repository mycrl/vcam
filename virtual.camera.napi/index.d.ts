export interface NV12Layout {
    size: number
    y: number
    uv: number
}

export default class VCam {
    constructor();
    getNV12Layout(width: number, height: number): NV12Layout;
    start(width: number, height: number): void;
    write(data: Buffer): void;
    stop(): void;
}