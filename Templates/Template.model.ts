import { dataSetter, IDynamicObject } from "xa-generics";

export class CMPModel {
    constructor(CV?: IDynamicObject) {
        if (!CV) return;

        for (let prop in this) {
            if (!(prop in CV)) continue;
            Object.assign(this, { [prop]: dataSetter(this[prop], CV[prop]) });
        }
    }
    // Model properties
    // ---

    // Own functions and properties
    // ---
}
