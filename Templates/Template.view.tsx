import { FC } from "react";
import { map } from "lodash";
import { ILang } from "../../../Interfaces/ILang.interface";
import { Add16 } from "@carbon/icons-react";
import { CMPModel } from "../Model/CMP.model";
import { FloatingError } from "xa-error-with-lang";
import { useTranslation } from "react-i18next";
import { Loading, Button } from "onemin-ui";
import { IError, ILoading, ISetState } from "xa-generics";
import { CMPElementView } from "./CMPElement.view";
import "./Less/CMPS.less";

export interface ICMPElementFunctions {}

export interface ICMPSViewProps extends ICMPElementFunctions {
    setError: ISetState<IError>;
    reloadCMPS: () => void;
    loading: ILoading;
    CVS: CMPModel[];
    error: IError;
}

export const CMPSView: FC<ICMPSViewProps> = (props) => {
    const { t } = useTranslation<ILang>();
    // On change and form rendering isn't wired by default.
    // You can put it into the element view to display the form if an edit button is clicked
    // or you can display the form instead of this mapping if the edit is clicked.
    return (
        <div className="global__view CVS-view">
            <Loading loading={props.loading} isFixed size={"MD"} />
            <FloatingError error={props.error} resetError={() => props.setError(null)} />

            <div className="global__controls">
                <Button size={"FIELD"} Icon={Add16} onClick={() => {}}>
                    {t<ILang>("add_new")}
                </Button>
            </div>
            <div className="global__list CVS-list-container">
                {map(props.CVS, (CV: CMPModel, index: number) => (
                    <CMPElementView key={`${index}-CV-element`} CV={CV} />
                ))}
            </div>
        </div>
    );
};
