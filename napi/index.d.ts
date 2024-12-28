export interface Layout {
    size: number;
    y: number;
    uv: number;
}

export default class VCam {
    constructor();
    get_nv12_layout(width: number, height: number): Layout;
    start(width: number, height: number): void;
    write(data: Buffer): void;
    stop(): void;
}
