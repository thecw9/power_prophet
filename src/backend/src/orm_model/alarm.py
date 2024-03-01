from datetime import datetime
from .measures import Measures
from .devices import Devices

from sqlalchemy import (
    BigInteger,
    ForeignKey,
    Column,
    Boolean,
    DateTime,
    Float,
    Integer,
    String,
    Table,
    JSON,
    LargeBinary,
    func,
)
from sqlalchemy.orm import Mapped, mapped_column
from src.config import Config

from .base import Base

config = Config()


def create_measure_alarms_monthly_table(table_name: str) -> Table:
    return Table(
        table_name,
        Base.metadata,
        Column(
            "key",
            BigInteger,
            ForeignKey(Measures.key),
            nullable=False,
            doc="告警测点Key",
        ),
        Column("time", DateTime, nullable=False, doc="告警时间"),
        Column("status", Integer, nullable=False, doc="告警状态"),
        Column("value", Float, nullable=True, doc="告警值"),
        Column("type", Integer, nullable=True, doc="0: 单测点告警, 1: 融合告警"),
    )


def create_device_alarms_monthly_table(table_name: str) -> Table:
    return Table(
        table_name,
        Base.metadata,
        Column(
            "key",
            BigInteger,
            ForeignKey(Devices.key),
            nullable=False,
            doc="告警设备Key",
        ),
        Column("time", DateTime, nullable=False, doc="告警时间"),
        Column("status", Integer, nullable=False, doc="告警状态"),
        Column("value", Float, nullable=True, doc="告警值"),
        Column("type", Integer, nullable=True, doc="0: 单设备告警, 1: 融合告警"),
    )
