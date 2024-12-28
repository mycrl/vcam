const vcam = new VCam();

const layout = vcam.get_nv12_layout(1920, 1080);
const buffer = Buffer.alloc(layout.size);

vcam.start();

for (;;) {
    vcam.write(buffer);
}
