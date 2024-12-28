"use strict";

const vcam = require("./build/Release/vcam-napi.node");

/**
 * Vcam
 *
 * @class
 */
module.exports = class Vcam {
    /**
     * @constructor
     */
    constructor() {
        this._raw = new vcam.VCam();
        this._runing = false;
    }

    /**
     *
     * @param   {[[Type]]} width  [[Description]]
     * @param   {[[Type]]} height [[Description]]
     * @returns {[[Type]]} [[Description]]
     */
    get_nv12_layout(width, height) {
        return this._raw.get_layout(width, height);
    }

    /**
     *
     */
    i420_to_nV12(width, height, buffer) {
        return this._raw.i420_to_nv12(width, height, buffer);
    }

    /**
     *
     */
    free_nv12(buffer) {
        return this._raw.free_nv12(buffer);
    }

    /**
     * @readonly
     * @typedef boolean
     */
    get runing() {
        return this._runing;
    }

    /**
     *
     * @param {[[number]]} width  [[Description]]
     * @param {[[number]]} height [[Description]]
     * @returns void
     * @public
     */
    start(width, height) {
        this._size = this.get_layout(width, height).size;
        this._raw.start(width, height);
        this._runing = true;
    }

    /**
     *
     * @param {[[Buffer]]} data [[Description]]
     * @returns void
     * @public
     */
    write(data) {
        if (data.length != this._size) {
            throw new Error("unexpected input");
        }

        this._raw.write(data);
    }

    /**
     * @returns void
     * @public
     */
    stop() {
        this._runing = false;
        this._raw.stop();
    }
};
