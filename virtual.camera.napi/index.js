'use strict'

const vcam = require('./build/Release/vcam.node')

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
        this._raw = new vcam.VCam()
        this._runing = false
    }
    
    /**
     * 
     * @param   {[[Type]]} width  [[Description]]
     * @param   {[[Type]]} height [[Description]]
     * @returns {[[Type]]} [[Description]]
     */
    getNV12Layout(width, height) {
        return this._raw.getNV12Layout(width, height)
    }
    
    /**
     * 
     */
    i420ToNV12(width, height, buffer) {
       return this._raw.i420ToNV12(width, height, buffer)
    }
    
    /**
     * 
     */
    freeNv12(buffer) {
       return this._raw.freeNv12(buffer)
    }
    
    /**
     * @readonly
     * @typedef boolean
     */
    get runing() {
        return this._runing
    }
    
    /**
     * 
     * @param {[[number]]} width  [[Description]]
     * @param {[[number]]} height [[Description]]
     * @returns void
     * @public
     */
    start(width, height) {
        this._size = this.getNV12Layout(width, height).size
        this._raw.start(width, height)
        this._runing = true
    }
    
    /**
     * 
     * @param {[[Buffer]]} data [[Description]]
     * @returns void
     * @public                      
     */
    write(data) {
        if (data.length != this._size)
            throw new Error('unexpected input')
        this._raw.write(data)
    }
    
    /**
     * @returns void
     * @public
     */
    stop() {
        this._runing = false
        this._raw.stop()
    }
}