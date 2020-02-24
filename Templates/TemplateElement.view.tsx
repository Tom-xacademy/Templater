import React from "react";
import { ICMPElementFunctions } from "./CMPS.view";
import { CMPModel } from "../Model/CMP.model";

export interface ICMPElementViewProps extends ICMPElementFunctions {
    CV: CMPModel;
}

const CMPElementView: React.FC<ICMPElementViewProps> = (props): React.ReactElement => {
    const CV: CMPModel = props.CV;
    return <div className="CV">{/* element content... */}</div>;
};

export default CMPElementView;
