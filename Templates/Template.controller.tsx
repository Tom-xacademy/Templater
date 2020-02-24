import React from "react";
import { CMPDAO } from "../CMP.dao";
import { CMPModel } from "../Model/CMP.model";
import { IError, ILoading } from "xa-generics";
import { useState, useEffect } from "react";
import CMPSView from "../View/CMPS.view";

export interface ICMPSProps {}

const CMPS: React.FC<ICMPSProps> = (props): React.ReactElement => {
    const [ CVS, set_CVS ] = useState<CMPModel[]>([]);
    const [ error, set_error ] = useState<IError>(null);
    const [ loading, set_loading ] = useState<ILoading>(null);

    const loadCMPS = (): void => {
        set_loading(
            CMPDAO.getCMPS()
                .then((CVSList: CMPModel[]) => {
                    set_CVS(CVSList);
                })
                .catch((error: IError) => {
                    set_error(error);
                })
                .finally(() => {
                    set_loading(null);
                })
        );
    };

    useEffect(
        () => {
            loadCMPS();
        },
        // eslint-disable-next-line
        []
    );

    return (
        <CMPSView
            CVS={CVS}
            error={error}
            loading={loading}
            reloadCMPS={loadCMPS}
            resetError={() => set_error(null)}
        />
    );
};

export default CMPS;
