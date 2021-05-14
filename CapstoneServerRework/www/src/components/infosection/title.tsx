import styled from 'styled-components';
import { Colors } from '../globalstyles';

export const InfoTitle = styled.h2`
    width: ${(props: { main?: boolean }) => (props.main ? '85%' : '100%')};
    margin: auto auto 5% auto;
    color: ${Colors.light};
    font-weight: 600;
    text-align: center;
`;