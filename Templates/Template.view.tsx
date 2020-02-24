import React from "react";
import { map } from "lodash";
import { CMPModel } from "../Model/CMP.model";
import { FloatingError } from "xa-generics";
import { IError, ILoading } from "xa-generics";
import CMPElementView from "./CMPElement.view";
import Spinner from "../../UI/Spinner/Spinner";
import "./Less/CMPS.less";

export interface ICMPElementFunctions {}

export interface ICMPSViewProps extends ICMPElementFunctions {
    resetError: () => void;
    reloadCMPS: () => void;
    loading: ILoading;
    CVS: CMPModel[];
    error: IError;
}

const CMPSView: React.FC<ICMPSViewProps> = (props): React.ReactElement => {
    // On change and form rendering isn't wired by default.
    // You can put it into the element view to display the form if an edit button is clicked
    // or you can display the form instead of this mapping if the edit is clicked.
    return (
        <div className="CVS-view">
            {props.loading && <Spinner />}
            <FloatingError error={props.error} resetError={props.resetError} />

            <div className="CVS-list-container">
                {map(props.CVS, (CV: CMPModel, index: number) => (
                    <CMPElementView key={`${index}-CV-element`} CV={CV} />
                ))}
            </div>
        </div>
    );
};

export default CMPSView;
