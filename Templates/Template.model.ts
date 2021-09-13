import { ModelConstructor, IDynamicObject } from "xa-generics";

export class CMPModel {
    constructor(rawData?: IDynamicObject<any>) {
        if (!rawData) return;
        const data = rawData as CMPMData;
        ModelConstructor(data, this);
    }

    id: string = "";
}

//If you add public methods, you may want to replace the empty string with them!
type CMPMData = Partial<InstanceType<typeof CMPModel>>;
