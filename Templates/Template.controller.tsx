import { CMPDAO } from "../DAO/CMP.dao";
import { CMPModel } from "../Model/CMP.model";
import { useState, FC } from "react";
import { CMPSView } from "../View/CMPS.view";
import { IError, ILoading, useDidMount } from "xa-generics";

export interface ICMPSProps {}

export const CMPS: FC<ICMPSProps> = (props) => {
    const [CVS, set_CVS] = useState<CMPModel[]>([]);
    const [error, setError] = useState<IError>(null);
    const [loading, setLoading] = useState<ILoading>(null);

    const loadCMPS = (): void => {
        setLoading(
            CMPDAO.getCMPS()
                .then((CVSList: CMPModel[]) => {
                    set_CVS(CVSList);
                })
                .catch((error: IError) => {
                    setError(error);
                })
                .finally(() => {
                    setLoading(null);
                })
        );
    };

    useDidMount(loadCMPS);

    return (
        <CMPSView
            CVS={CVS}
            error={error}
            loading={loading}
            setError={setError}
            reloadCMPS={loadCMPS}
        />
    );
};
