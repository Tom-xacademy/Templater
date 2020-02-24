import { axios } from "xa-generics";
import { CMPModel } from "../Model/CMP.model";
import { IDynamicObject } from "xa-generics";
import { AxiosPromise, AxiosResponse } from "axios";

export abstract class CMPDAO {
    private static readonly base: string = "/api/CVS";

    public static async getCMPS(): Promise<CMPModel[]> {
        const request: AxiosPromise<IDynamicObject[]> = axios.getInstance().get(this.base);
        const response: AxiosResponse<IDynamicObject[]> = await request;
        return response.data.map((CV: IDynamicObject) => new CMPModel(CV));
    }
}
