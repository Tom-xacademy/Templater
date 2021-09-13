import { ICMPElementFunctions } from "./CMPS.view";
import { CMPModel } from "../Model/CMP.model";
import { FC } from "react";

export interface ICMPElementViewProps extends ICMPElementFunctions {
    CV: CMPModel;
}

export const CMPElementView: FC<ICMPElementViewProps> = (props) => {
    const CV: CMPModel = props.CV;
    return <div className="CV">{/* element content... */}</div>;
};
